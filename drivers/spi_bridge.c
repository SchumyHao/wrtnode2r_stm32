/* Includes ------------------------------------------------------------------*/
#include <rtdevice.h>
#include <rthw.h>
#include <rtthread.h>
#include "wrtnode2r_board.h"
#include "wirish/wirish.h"

/************  SPI Bridge  **************/
#define SPI_BRIDGE_MAX_DATA_LEN         (1024)
#define SPI_BRIDGE_ONE_FRAME_MAX_LEN    (255)

struct spi_bridge {
	struct rt_device parent;

	rt_uint8_t read_buf_pool[SPI_BRIDGE_MAX_DATA_LEN];
	struct rt_ringbuffer read_buf;

	rt_uint8_t write_buf_pool[SPI_BRIDGE_MAX_DATA_LEN];
	struct rt_ringbuffer write_buf;

#define SPI_BRIDGE_STATUS_7688_READ_FROM_STM32_E    (1<<0)
#define SPI_BRIDGE_STATUS_7688_READ_FROM_STM32_NE   (0<<0)
#define SPI_BRIDGE_STATUS_7688_WRITE_TO_STM32_F     (1<<1)
#define SPI_BRIDGE_STATUS_7688_WRITE_TO_STM32_NF    (0<<1)
#define SPI_BRIDGE_STATUS_SET_PARAMETER_ERR         (1<<2)
#define SPI_BRIDGE_STATUS_SET_PARAMETER_OK          (0<<2)
#define SPI_BRIDGE_STATUS_CHECK_ERR                 (1<<3)
#define SPI_BRIDGE_STATUS_CHECK_OK                  (0<<3)
#define SPI_BRIDGE_STATUS_OK                        (0x50)
#define SPI_BRIDGE_STATUS_HEAD_MASK                 (0xf0)
#define SPI_BRIDGE_STATUS_ERR_MASK                  (0x0f)
#define SPI_BRIDGE_STATUS_NULL                      (0x00)
	rt_uint8_t status;

#define SPI_BRIDGE_CMD_GET_STATUS                   (1U)
#define SPI_BRIDGE_CMD_7688_READ_FROM_STM32         (10U)
#define SPI_BRIDGE_CMD_7688_WRITE_TO_STM32          (20U)
#define SPI_BRIDGE_CMD_SET_BLOCK_LEN                (30U)
#define SPI_BRIDGE_CMD_NULL                         (0U)
	rt_uint8_t cmd;

	/* status of FSM */
#define SPI_BRIDGE_FSM_7688_READ_FROM_STM32         (2U)
#define SPI_BRIDGE_FSM_7688_WRITE_TO_STM32          (3U)
#define SPI_BRIDGE_FSM_SET_BLOCK_LEN                (4U)
#define SPI_BRIDGE_FSM_SEND_RESP                    (5U)
#define SPI_BRIDGE_FSM_SEND_END_RESP                (6U)
#define SPI_BRIDGE_FSM_RECV_END_RESP                (7U)
#define SPI_BRIDGE_FSM_NULL                         (0U)
	rt_uint8_t fsm_status;
	rt_uint8_t fsm_status_next;

	/* block length */
#define SPI_BRIDGE_LEN_8_BYTES                      (8U)
#define SPI_BRIDGE_LEN_16_BYTES                     (16U)
#define SPI_BRIDGE_LEN_32_BYTES                     (32U)
	rt_uint8_t len;
	/* in block length count */
	rt_uint8_t count;
	rt_uint8_t* xfet_buf;

	/* Check error flag */
	bool chk_err;
	/* Set parameters error flag */
	bool set_err;
};

static struct spi_bridge spi_bridge;

static inline bool _is_stm32_read_buf_empty(void)
{
	return (RT_RINGBUFFER_EMPTY == rt_ringbuffer_status(&spi_bridge.read_buf));
}

static inline bool _is_stm32_read_buf_full(void)
{
	return (RT_RINGBUFFER_FULL == rt_ringbuffer_status(&spi_bridge.read_buf));
}

static inline bool _is_stm32_write_buf_empty(void)
{
	return (RT_RINGBUFFER_EMPTY == rt_ringbuffer_status(&spi_bridge.write_buf));
}

static inline bool _is_stm32_write_buf_full(void)
{
	return (RT_RINGBUFFER_FULL == rt_ringbuffer_status(&spi_bridge.write_buf));
}

static inline rt_uint16_t spi_bridge_get_write_buf_len(void)
{
	return rt_ringbuffer_data_len(&spi_bridge.write_buf);
}

static inline rt_uint16_t spi_bridge_get_read_buf_len(void)
{
	return rt_ringbuffer_data_len(&spi_bridge.read_buf);
}

static inline bool _is_spi_bridge_status_head_ok(uint8_t status)
{
	return (status & SPI_BRIDGE_STATUS_HEAD_MASK) == SPI_BRIDGE_STATUS_OK;
}

static inline bool _can_spi_bridge_status_read(uint8_t status)
{
	return !(status & SPI_BRIDGE_STATUS_7688_READ_FROM_STM32_E);
}

static inline bool _can_spi_bridge_status_write(uint8_t status)
{
	return !(status & SPI_BRIDGE_STATUS_7688_WRITE_TO_STM32_F);
}

static inline bool _is_spi_bridge_status_set_ok(uint8_t status)
{
	return !(status & SPI_BRIDGE_STATUS_SET_PARAMETER_ERR);
}

static inline bool _is_spi_bridge_status_check_ok(uint8_t status)
{
	return !(status & SPI_BRIDGE_STATUS_CHECK_ERR);
}

static inline bool _is_spi_bridge_status_ok(uint8_t status)
{
	return !(status & SPI_BRIDGE_STATUS_ERR_MASK);
}


static rt_uint8_t spi_bridge_get_status(void)
{
	rt_uint8_t status = SPI_BRIDGE_STATUS_OK;

	if (spi_bridge.len > (SPI_BRIDGE_MAX_DATA_LEN - spi_bridge_get_read_buf_len()))
		/* Full! Can not write to stm32 */
		status |= SPI_BRIDGE_STATUS_7688_WRITE_TO_STM32_F;

	if (_is_stm32_write_buf_empty())
		/* Can read from stm32 */
		status |= SPI_BRIDGE_STATUS_7688_READ_FROM_STM32_E;
	if (spi_bridge.chk_err)
		status |= SPI_BRIDGE_STATUS_CHECK_ERR;
	if (spi_bridge.set_err)
		status |= SPI_BRIDGE_STATUS_SET_PARAMETER_ERR;

	return status;
}

static rt_err_t spi_bridge_init(rt_device_t dev)
{
	rt_ringbuffer_init(&spi_bridge.read_buf, spi_bridge.read_buf_pool,
					   SPI_BRIDGE_MAX_DATA_LEN);
	rt_ringbuffer_init(&spi_bridge.write_buf, spi_bridge.write_buf_pool,
					   SPI_BRIDGE_MAX_DATA_LEN);
	/* default spi_bridge len is 16 */
	spi_bridge.xfet_buf = rt_malloc(SPI_BRIDGE_LEN_16_BYTES * sizeof(rt_uint8_t));
	if (spi_bridge.xfet_buf == RT_NULL)
		return -RT_ENOMEM;
	spi_bridge.len = SPI_BRIDGE_LEN_16_BYTES;

	return RT_EOK;
}

static rt_err_t spi_bridge_open(rt_device_t dev, rt_uint16_t oflag)
{
	dev->flag = oflag | RT_DEVICE_FLAG_INT_RX;
	dev->open_flag = oflag & 0xff;

	spi1.beginSlave_order_mode(MSBFIRST, SPI_MODE_1);

	return RT_EOK;
}

static rt_size_t spi_bridge_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	return rt_ringbuffer_get(&spi_bridge.read_buf, buffer, size);
}

static rt_size_t spi_bridge_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
	return rt_ringbuffer_put(&spi_bridge.write_buf, buffer, size);
}

void spi_bridge_register(const char* name)
{
	rt_memset(&spi_bridge, 0, sizeof(spi_bridge));
	/* register device */
	spi_bridge.parent.type = RT_Device_Class_Miscellaneous;
	spi_bridge.parent.init = spi_bridge_init;
	spi_bridge.parent.open = spi_bridge_open;
	spi_bridge.parent.close = RT_NULL;
	spi_bridge.parent.read = spi_bridge_read;
	spi_bridge.parent.write = spi_bridge_write;
	spi_bridge.parent.control = RT_NULL;
	/* no private */
	spi_bridge.parent.user_data = RT_NULL;

	rt_device_register(&spi_bridge.parent, name, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STANDALONE);
}

static inline bool is_valid_cmd(rt_uint8_t cmd)
{
	return ((SPI_BRIDGE_CMD_GET_STATUS == cmd)
			|| (SPI_BRIDGE_CMD_7688_READ_FROM_STM32 == cmd)
			|| (SPI_BRIDGE_CMD_7688_WRITE_TO_STM32 == cmd)
			|| (SPI_BRIDGE_CMD_SET_BLOCK_LEN == cmd));
}

static inline bool is_valid_len(rt_uint8_t len)
{
	return ((SPI_BRIDGE_LEN_8_BYTES == len)
			|| (SPI_BRIDGE_LEN_16_BYTES == len)
			|| (SPI_BRIDGE_LEN_32_BYTES == len));
}

static inline rt_uint8_t calulate_check(void)
{
	int i;
	rt_uint8_t chk = 0;
	rt_uint8_t* ptr = spi_bridge.xfet_buf;
	for (i = spi_bridge.len; i > 0; i--) {
		chk ^= *ptr++;
	}
	return chk;
}

static inline void spi_bridge_disable_spi_int(void)
{
	spi_irq_disable(spi1.c_dev(), SPI_CR2_RXNEIE);
}

static inline void spi_bridge_enable_spi_int(void)
{
	spi_irq_enable(spi1.c_dev(), SPI_CR2_RXNEIE);
}

static inline void spi_bridge_send_ch(rt_uint8_t ch)
{
	spi_bridge_disable_spi_int();
	spi1.write(ch);
	log_text[pos++] = ch;
	spi_bridge_enable_spi_int();
}

static inline void spi_bridge_send_resp(rt_uint8_t resp)
{
	spi_bridge_send_ch(resp);
}

static inline rt_size_t spi_bridge_7688_write_to_stm32(const rt_uint8_t* data, rt_uint16_t len)
{
	return rt_ringbuffer_put(&spi_bridge.read_buf, data, len);
}

static inline rt_size_t spi_bridge_7688_read_from_stm32(rt_uint8_t* data, rt_uint16_t len)
{
	return rt_ringbuffer_get(&spi_bridge.write_buf, data, len);
}

static void spi_bridge_rx_isr(rt_uint8_t ch)
{
	spi_bridge.fsm_status = spi_bridge.fsm_status_next;

	switch (spi_bridge.fsm_status) {
	case SPI_BRIDGE_FSM_NULL:
		if (is_valid_cmd(ch)) {
			spi_bridge.status = spi_bridge_get_status();
			spi_bridge_send_resp(spi_bridge.status);
			spi_bridge.cmd = ch;
			if (SPI_BRIDGE_CMD_GET_STATUS == ch)
				spi_bridge.fsm_status_next = SPI_BRIDGE_FSM_SEND_END_RESP;
			else
				spi_bridge.fsm_status_next = SPI_BRIDGE_FSM_SEND_RESP;
		} else {
			spi_bridge_send_ch(0);
		}
		break;
	case SPI_BRIDGE_FSM_SEND_RESP:
		/* write spi data reg first if change to write status */
		if (SPI_BRIDGE_CMD_SET_BLOCK_LEN == spi_bridge.cmd) {
			spi_bridge.fsm_status_next = SPI_BRIDGE_FSM_SET_BLOCK_LEN;
			spi_bridge_send_ch(0);
		} else if (SPI_BRIDGE_CMD_7688_WRITE_TO_STM32 == spi_bridge.cmd) {
			spi_bridge_send_ch(0);
			if (!_can_spi_bridge_status_write(spi_bridge.status)) {
				spi_bridge.cmd = SPI_BRIDGE_CMD_NULL;
				spi_bridge.fsm_status_next = SPI_BRIDGE_FSM_NULL;
				break;
			}
			spi_bridge.count = 0;
			spi_bridge.fsm_status_next = SPI_BRIDGE_FSM_7688_WRITE_TO_STM32;
		} else if (SPI_BRIDGE_CMD_7688_READ_FROM_STM32 == spi_bridge.cmd) {
			if (!_can_spi_bridge_status_read(spi_bridge.status)) {
				spi_bridge.cmd = SPI_BRIDGE_CMD_NULL;
				spi_bridge.fsm_status_next = SPI_BRIDGE_FSM_NULL;
				spi_bridge_send_ch(0);
				break;
			}
			rt_memset(spi_bridge.xfet_buf, 0, spi_bridge.len * sizeof(rt_uint8_t));
			spi_bridge_7688_read_from_stm32(spi_bridge.xfet_buf, spi_bridge.len);
			spi_bridge_send_ch(spi_bridge.xfet_buf[0]);
			spi_bridge.count = 1;
			spi_bridge.fsm_status_next = SPI_BRIDGE_FSM_7688_READ_FROM_STM32;
		}
		break;
	case SPI_BRIDGE_FSM_SET_BLOCK_LEN:
		if (!is_valid_len(ch)) {
			spi_bridge.set_err = true;
			goto SPI_BRIDGE_FSM_SET_BLOCK_LEN_OUT;
		}
		if (ch == spi_bridge.len) {
			spi_bridge.set_err = false;
			goto SPI_BRIDGE_FSM_SET_BLOCK_LEN_OUT;
		}
		if (spi_bridge.xfet_buf != RT_NULL)
			rt_free(spi_bridge.xfet_buf);
		spi_bridge.xfet_buf = rt_malloc(ch * sizeof(rt_uint8_t));
		if (spi_bridge.xfet_buf == RT_NULL) {
			spi_bridge.set_err = true;
			goto SPI_BRIDGE_FSM_SET_BLOCK_LEN_OUT;
		}
		spi_bridge.len = ch;
		spi_bridge.set_err = false;
SPI_BRIDGE_FSM_SET_BLOCK_LEN_OUT:
		spi_bridge.status = spi_bridge_get_status();
		spi_bridge_send_resp(spi_bridge.status);
		spi_bridge.fsm_status_next = SPI_BRIDGE_FSM_SEND_END_RESP;
		break;
	case SPI_BRIDGE_FSM_7688_WRITE_TO_STM32:
		if (spi_bridge.count < spi_bridge.len) {
			spi_bridge_send_ch(0);
			spi_bridge.xfet_buf[spi_bridge.count++] = ch;
			break;
		}
		if (ch != calulate_check()) {
			spi_bridge.chk_err = true;
			goto SPI_BRIDGE_FSM_7688_WRITE_TO_STM32_OUT;
		}
		spi_bridge.chk_err = false;
		spi_bridge_7688_write_to_stm32(spi_bridge.xfet_buf, spi_bridge.len);
		if (spi_bridge.parent.rx_indicate != RT_NULL)
			spi_bridge.parent.rx_indicate(&spi_bridge.parent, spi_bridge_get_read_buf_len());
SPI_BRIDGE_FSM_7688_WRITE_TO_STM32_OUT:
		spi_bridge.status = spi_bridge_get_status();
		spi_bridge_send_resp(spi_bridge.status);
		spi_bridge.fsm_status_next = SPI_BRIDGE_FSM_SEND_END_RESP;
		spi_bridge.count = 0;
		break;
	case SPI_BRIDGE_FSM_7688_READ_FROM_STM32:
		if (spi_bridge.count < spi_bridge.len) {
			spi_bridge_send_ch(spi_bridge.xfet_buf[spi_bridge.count++]);
			break;
		}
		if (spi_bridge.count++ == spi_bridge.len) {
			spi_bridge_send_ch(calulate_check());
			break;
		}
		spi_bridge_send_ch(0);
		spi_bridge.fsm_status_next = SPI_BRIDGE_FSM_RECV_END_RESP;
		spi_bridge.count = 0;
		break;
	case SPI_BRIDGE_FSM_RECV_END_RESP:
		if (!_is_spi_bridge_status_head_ok(ch) ||
			!_is_spi_bridge_status_check_ok(ch)) {
			spi_bridge.status |= SPI_BRIDGE_STATUS_CHECK_ERR;
		}
	case SPI_BRIDGE_FSM_SEND_END_RESP:
	default:
		spi_bridge.cmd = SPI_BRIDGE_CMD_NULL;
		spi_bridge.fsm_status_next = SPI_BRIDGE_FSM_NULL;
		break;
	}
}

void SPI1_IRQHandler(void)
{
	rt_interrupt_enter();
	if (spi_is_rx_nonempty(spi1.c_dev())) {
		nvic_irq_disable(NVIC_SPI1);
		spi_bridge_rx_isr(spi1.read());
		nvic_irq_enable(NVIC_SPI1);
	}
	rt_interrupt_leave();
}

