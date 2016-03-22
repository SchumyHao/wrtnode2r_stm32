/* Includes ------------------------------------------------------------------*/
#include <rtdevice.h>
#include <rthw.h>
#include <rtthread.h>
#include "wrtnode2r_board.h"
#include "wirish/wirish.h"
#include "libmaple/dma.h"

/************  SPI Bridge  **************/
#define SPI_BRIDGE_MAX_DATA_LEN         (1024)
#define SPI_BRIDGE_ONE_FRAME_MAX_LEN    (255)
#define SPI_BRIDGE_MAILBOX_SIZE         (5)
#define SPI_BRIDGE_MAILBOX_NAME         "bmb"
#define SPI_BRIDGE_ENTRY_STACK_SIZE     (1024)
#define SPI_BRIDGE_ENTRY_PRIO           (3)
#define SPI_BRIDGE_ENTRY_TICK           (20)

struct spi_bridge {
	struct rt_device parent;

	rt_uint8_t read_buf_pool[SPI_BRIDGE_MAX_DATA_LEN];
	struct rt_ringbuffer read_buf;

	rt_uint8_t write_buf_pool[SPI_BRIDGE_MAX_DATA_LEN];
	struct rt_ringbuffer write_buf;

	rt_mailbox_t mb;
	rt_thread_t tid;

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

static void spi_bridge_entry(void* parameter);
static rt_err_t spi_bridge_init(rt_device_t dev)
{
	rt_ringbuffer_init(&spi_bridge.read_buf, spi_bridge.read_buf_pool,
					   SPI_BRIDGE_MAX_DATA_LEN);
	rt_ringbuffer_init(&spi_bridge.write_buf, spi_bridge.write_buf_pool,
					   SPI_BRIDGE_MAX_DATA_LEN);
	/* default spi_bridge len is 16. +1 is for check byte or resp byte */
	spi_bridge.xfet_buf = rt_malloc((SPI_BRIDGE_LEN_16_BYTES + 1) * sizeof(rt_uint8_t));
	if (spi_bridge.xfet_buf == RT_NULL)
		return -RT_ENOMEM;
	spi_bridge.len = SPI_BRIDGE_LEN_16_BYTES;

	spi_bridge.mb = rt_mb_create(SPI_BRIDGE_MAILBOX_NAME, SPI_BRIDGE_MAILBOX_SIZE, RT_IPC_FLAG_FIFO);
	if (spi_bridge.mb == RT_NULL)
		return -RT_ERROR;

	spi_bridge.tid = rt_thread_create("bridge", spi_bridge_entry, RT_NULL, SPI_BRIDGE_ENTRY_STACK_SIZE, SPI_BRIDGE_ENTRY_PRIO, SPI_BRIDGE_ENTRY_TICK);
	if (spi_bridge.tid == RT_NULL)
		return -RT_ERROR;
	rt_thread_startup(spi_bridge.tid);

	return RT_EOK;
}

static rt_err_t spi_bridge_open(rt_device_t dev, rt_uint16_t oflag)
{
	dev->flag = oflag | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_DMA_RX | RT_DEVICE_FLAG_DMA_TX;
	dev->open_flag = oflag & 0xff;

	spi1.beginSlave_order_mode(MSBFIRST, SPI_MODE_1);
	dma_init(DMA1);

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

static inline void spi_bridge_disable_spi_rx_int(void)
{
	spi_irq_disable(spi1.c_dev(), SPI_CR2_RXNEIE);
}

static inline void spi_bridge_disable_spi_int(void)
{
	nvic_irq_disable(NVIC_SPI1);
}

static inline void spi_bridge_enable_spi_rx_int(void)
{
	spi_irq_enable(spi1.c_dev(), SPI_CR2_RXNEIE);
}

static inline void spi_bridge_enable_spi_int(void)
{
	nvic_irq_enable(NVIC_SPI1);
}

static inline rt_uint8_t spi_bridge_recv_ch(void)
{
	spi1.read();
}

static inline void spi_bridge_send_ch(rt_uint8_t ch)
{
	spi1.write(ch);
}

static inline void spi_bridge_send_resp(rt_uint8_t resp)
{
	spi1.write(resp);
}

static inline rt_size_t spi_bridge_7688_write_to_stm32(const rt_uint8_t* data, rt_uint16_t len)
{
	return rt_ringbuffer_put(&spi_bridge.read_buf, data, len);
}

static inline rt_size_t spi_bridge_7688_read_from_stm32(rt_uint8_t* data, rt_uint16_t len)
{
	return rt_ringbuffer_get(&spi_bridge.write_buf, data, len);
}

static void spi_bridge_dma_rx_irq_handler(void)
{
	dma_irq_cause cause;
	rt_interrupt_enter();

	cause = dma_get_irq_cause(DMA1, DMA_CH2);
	if (DMA_TRANSFER_COMPLETE == cause) {
		rt_mb_send(spi_bridge.mb, 0);
	}
	if (DMA_TRANSFER_ERROR == cause) {
		rt_mb_send(spi_bridge.mb, 1);
	}

	rt_interrupt_leave();
}

static int spi_bridge_set_dma_rx(void)
{
	dma_tube_config dma_cfg;

	dma_cfg.tube_src = &spi1.c_dev()->regs->DR;
	dma_cfg.tube_src_size = DMA_SIZE_8BITS;
	dma_cfg.tube_dst = spi_bridge.xfet_buf;
	dma_cfg.tube_dst_size = DMA_SIZE_8BITS;
	dma_cfg.tube_nr_xfers = spi_bridge.len + 1;
	dma_cfg.tube_flags = DMA_CFG_DST_INC | DMA_CFG_CMPLT_IE | DMA_CFG_ERR_IE;
	dma_cfg.target_data = NULL;
	dma_cfg.tube_req_src = DMA_REQ_SRC_SPI1_RX;

	if (dma_tube_cfg(DMA1, DMA_CH2, &dma_cfg) < 0) {
		return -1;
	}

	dma_attach_interrupt(DMA1, DMA_CH2, spi_bridge_dma_rx_irq_handler);
}

static inline void spi_bridge_enable_spi_rx_dma(void)
{
	spi_rx_dma_enable(spi1.c_dev());
	dma_enable(DMA1, DMA_CH2);
}

static inline void spi_bridge_disable_spi_rx_dma(void)
{
	dma_disable(DMA1, DMA_CH2);
	spi_rx_dma_disable(spi1.c_dev());
}


static void spi_bridge_dma_tx_irq_handler(void)
{
	dma_irq_cause cause;
	rt_interrupt_enter();

	cause = dma_get_irq_cause(DMA1, DMA_CH3);
	if (DMA_TRANSFER_COMPLETE == cause) {
		rt_mb_send(spi_bridge.mb, 0);
	}
	if (DMA_TRANSFER_ERROR == cause) {
		rt_mb_send(spi_bridge.mb, 1);
	}

	rt_interrupt_leave();
}

static int spi_bridge_set_dma_tx(void)
{
	dma_tube_config dma_cfg;

	dma_cfg.tube_src = spi_bridge.xfet_buf;
	dma_cfg.tube_src_size = DMA_SIZE_8BITS;
	dma_cfg.tube_dst = &spi1.c_dev()->regs->DR;
	dma_cfg.tube_dst_size = DMA_SIZE_8BITS;
	dma_cfg.tube_nr_xfers = spi_bridge.len + 1;
	dma_cfg.tube_flags = DMA_CFG_SRC_INC | DMA_CFG_CMPLT_IE | DMA_CFG_ERR_IE;
	dma_cfg.target_data = NULL;
	dma_cfg.tube_req_src = DMA_REQ_SRC_SPI1_TX;

	if (dma_tube_cfg(DMA1, DMA_CH3, &dma_cfg) < 0) {
		return -1;
	}

	dma_attach_interrupt(DMA1, DMA_CH3, spi_bridge_dma_tx_irq_handler);
}

static inline void spi_bridge_enable_spi_tx_dma(void)
{
	spi_tx_dma_enable(spi1.c_dev());
	dma_enable(DMA1, DMA_CH3);
}

static inline void spi_bridge_disable_spi_tx_dma(void)
{
	dma_disable(DMA1, DMA_CH3);
	spi_tx_dma_disable(spi1.c_dev());
}

static inline bool spi_bridge_cmd_prepare(rt_uint8_t cmd)
{
	spi_bridge.status = spi_bridge_get_status();
	if ((cmd == SPI_BRIDGE_CMD_7688_WRITE_TO_STM32) &&
		_can_spi_bridge_status_write(spi_bridge.status)) {
		if (spi_bridge_set_dma_rx() < 0)
			return false;
	} else if ((cmd == SPI_BRIDGE_CMD_7688_READ_FROM_STM32) &&
			   _can_spi_bridge_status_read(spi_bridge.status)) {
		rt_memset(spi_bridge.xfet_buf, 0, spi_bridge.len * sizeof(rt_uint8_t));
		spi_bridge_7688_read_from_stm32(spi_bridge.xfet_buf, spi_bridge.len);
		spi_bridge.xfet_buf[spi_bridge.len] = calulate_check();
		if (spi_bridge_set_dma_tx() < 0)
			return false;
	} else if (cmd == SPI_BRIDGE_CMD_SET_BLOCK_LEN) {
		/* Nothong to be prepare */
	} else if (cmd == SPI_BRIDGE_CMD_GET_STATUS) {
		/* Nothong to be prepare */
	} else {
		return false;
	}
	return true;
}
static int rx_count;
static void spi_bridge_entry(void* parameter)
{
	rt_uint32_t value;
	rt_uint8_t ch;

	while (1) {
		if (rt_mb_recv(spi_bridge.mb, &value, RT_WAITING_FOREVER) < 0) {
			return;
		}
		ch = (rt_uint8_t)value;
		rx_count--;

		spi_bridge.fsm_status = spi_bridge.fsm_status_next;

		switch (spi_bridge.fsm_status) {
		case SPI_BRIDGE_FSM_NULL:
			if (is_valid_cmd(ch) && spi_bridge_cmd_prepare(ch)) {
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
				spi_bridge_send_ch(0);
				spi_bridge.fsm_status_next = SPI_BRIDGE_FSM_SET_BLOCK_LEN;
			} else if (SPI_BRIDGE_CMD_7688_WRITE_TO_STM32 == spi_bridge.cmd) {
				spi_bridge_disable_spi_rx_int();
				spi_bridge_enable_spi_rx_dma();
				//spi_bridge_send_ch(0);
				spi_bridge.fsm_status_next = SPI_BRIDGE_FSM_7688_WRITE_TO_STM32;
			} else if (SPI_BRIDGE_CMD_7688_READ_FROM_STM32 == spi_bridge.cmd) {
				spi_bridge_disable_spi_rx_int();
				spi_bridge_enable_spi_tx_dma();
				spi_bridge.fsm_status_next = SPI_BRIDGE_FSM_7688_READ_FROM_STM32;
			}
			break;
		case SPI_BRIDGE_FSM_SET_BLOCK_LEN:
			if (!is_valid_len(ch)) {
				spi_bridge.set_err = true;
				spi_bridge.status |= SPI_BRIDGE_STATUS_SET_PARAMETER_ERR;
				goto SPI_BRIDGE_FSM_SET_BLOCK_LEN_OUT;
			}
			if (ch == spi_bridge.len) {
				spi_bridge.set_err = false;
				spi_bridge.status &= ~SPI_BRIDGE_STATUS_SET_PARAMETER_ERR;
				goto SPI_BRIDGE_FSM_SET_BLOCK_LEN_OUT;
			}
			if (spi_bridge.xfet_buf != RT_NULL)
				rt_free(spi_bridge.xfet_buf);
			spi_bridge.xfet_buf = rt_malloc(ch * sizeof(rt_uint8_t));
			if (spi_bridge.xfet_buf == RT_NULL) {
				spi_bridge.set_err = true;
				spi_bridge.status |= SPI_BRIDGE_STATUS_SET_PARAMETER_ERR;
				goto SPI_BRIDGE_FSM_SET_BLOCK_LEN_OUT;
			}
			spi_bridge.len = ch;
			spi_bridge.set_err = false;
			spi_bridge.status &= ~SPI_BRIDGE_STATUS_SET_PARAMETER_ERR;
SPI_BRIDGE_FSM_SET_BLOCK_LEN_OUT:
			spi_bridge_send_resp(spi_bridge.status);
			spi_bridge.fsm_status_next = SPI_BRIDGE_FSM_SEND_END_RESP;
			break;
		case SPI_BRIDGE_FSM_7688_WRITE_TO_STM32:
			spi_bridge_disable_spi_rx_dma();
			spi_bridge_enable_spi_rx_int();
			if (ch != 0) {
				spi_bridge.cmd = SPI_BRIDGE_CMD_NULL;
				spi_bridge.fsm_status_next = SPI_BRIDGE_FSM_NULL;
				break;
			}
			if (spi_bridge.xfet_buf[spi_bridge.len] == calulate_check()) {
				spi_bridge.chk_err = false;
				spi_bridge.status &= ~SPI_BRIDGE_STATUS_CHECK_ERR;
				spi_bridge_7688_write_to_stm32(spi_bridge.xfet_buf, spi_bridge.len);
			} else {
				spi_bridge.chk_err = true;
				spi_bridge.status |= SPI_BRIDGE_STATUS_CHECK_ERR;
			}
			spi_bridge_send_resp(spi_bridge.status);
			spi_bridge.fsm_status_next = SPI_BRIDGE_FSM_SEND_END_RESP;
			break;
		case SPI_BRIDGE_FSM_7688_READ_FROM_STM32:
			spi_bridge_disable_spi_tx_dma();
			spi_bridge_recv_ch();
			spi_bridge_enable_spi_rx_int();
			if (ch != 0) {
				spi_bridge.cmd = SPI_BRIDGE_CMD_NULL;
				spi_bridge.fsm_status_next = SPI_BRIDGE_FSM_NULL;
				break;
			}
			spi_bridge_send_ch(0);
			spi_bridge.fsm_status_next = SPI_BRIDGE_FSM_RECV_END_RESP;
			break;
		case SPI_BRIDGE_FSM_RECV_END_RESP:
			if (!_is_spi_bridge_status_head_ok(ch) ||
				!_is_spi_bridge_status_check_ok(ch)) {
				spi_bridge.status |= SPI_BRIDGE_STATUS_CHECK_ERR;
			}
		case SPI_BRIDGE_FSM_SEND_END_RESP:
		default:
			if ((SPI_BRIDGE_CMD_7688_WRITE_TO_STM32 == spi_bridge.cmd)
				&& (!spi_bridge.chk_err)
				&& (spi_bridge.parent.rx_indicate != RT_NULL)) {
				spi_bridge.parent.rx_indicate(&spi_bridge.parent, spi_bridge_get_read_buf_len());
			}
			spi_bridge.cmd = SPI_BRIDGE_CMD_NULL;
			spi_bridge.fsm_status_next = SPI_BRIDGE_FSM_NULL;
			break;
		}
	}
}

void SPI1_IRQHandler(void)
{
	rt_interrupt_enter();
	if (spi_is_rx_nonempty(spi1.c_dev())) {
		spi_bridge_disable_spi_int();
		rt_mb_send(spi_bridge.mb, spi1.read());
		rx_count++;
		spi_bridge_enable_spi_int();
	}
	rt_interrupt_leave();
}