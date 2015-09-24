/* Includes ------------------------------------------------------------------*/
#include <rtdevice.h>
#include <rthw.h>
#include <rtthread.h>
#include "board.h"
#include "wirish/wirish.h"

#define WRTNODE2R_SPI_CMD_7688_READ_FROM_STM32         (0x01)
#define WRTNODE2R_SPI_CMD_7688_READ_FROM_SRM32_LEN     (0x04)
#define WRTNODE2R_SPI_CMD_7688_WRITE_TO_STM32          (0x10)
#define WRTNODE2R_SPI_CMD_7688_WRITE_TO_STM32_LEN      (0x40)

#define WRTNODE2R_SPI_CMD_GET_STATUS                   (0xFF)
#define WRTNODE2R_SPI_STATUS_7688_READ_FROM_STM32_E    (1<<0)
#define WRTNODE2R_SPI_STATUS_7688_READ_FROM_STM32_NE   (0<<0)
#define WRTNODE2R_SPI_STATUS_7688_WRITE_TO_STM32_F     (1<<1)
#define WRTNODE2R_SPI_STATUS_7688_WRITE_TO_STM32_NF    (0<<1)
#define WRTNODE2R_SPI_STATUS_OK                        (0x80)

#define WRTNODE2R_SPI_READ_ALL                         (0xFF)

/************  WRTnode2r SPI Bridge  **************/
#define WRTNODE2R_SPI_MAX_DATA_LEN         (255)

struct wrtnode2r_spi_bridge {
    struct rt_device parent;

    rt_uint8_t read_buf_pool[WRTNODE2R_SPI_MAX_DATA_LEN];
    struct rt_ringbuffer read_buf;

    rt_uint8_t write_buf_pool[WRTNODE2R_SPI_MAX_DATA_LEN];
    struct rt_ringbuffer write_buf;
    rt_uint8_t status;
};

static struct wrtnode2r_spi_bridge spi_bridge;

static inline rt_uint8_t _is_wrtnode2r_spi_stm32_read_buf_empty(void)
{
    return (RT_RINGBUFFER_EMPTY == rt_ringbuffer_status(&spi_bridge.read_buf));
}

static inline rt_uint8_t _is_wrtnode2r_spi_stm32_read_buf_full(void)
{
    return (RT_RINGBUFFER_FULL == rt_ringbuffer_status(&spi_bridge.read_buf));
}

static inline rt_uint8_t _is_wrtnode2r_spi_stm32_write_buf_empty(void)
{
    return (RT_RINGBUFFER_EMPTY == rt_ringbuffer_status(&spi_bridge.write_buf));
}

static inline rt_uint8_t _is_wrtnode2r_spi_stm32_write_buf_full(void)
{
    return (RT_RINGBUFFER_FULL == rt_ringbuffer_status(&spi_bridge.write_buf));
}

static rt_uint8_t wrtnode2r_spi_stm32_get_status(void)
{
    rt_uint8_t wrtnode2r_spi_status = WRTNODE2R_SPI_STATUS_OK;

    if(_is_wrtnode2r_spi_stm32_read_buf_full()) {
        /* Full! Can not write to stm32 */
        wrtnode2r_spi_status |= WRTNODE2R_SPI_STATUS_7688_WRITE_TO_STM32_F;
    }

    if(_is_wrtnode2r_spi_stm32_write_buf_empty()) {
        /* Can read from stm32 */
        wrtnode2r_spi_status |= WRTNODE2R_SPI_STATUS_7688_READ_FROM_STM32_E;
    }
    return wrtnode2r_spi_status;
}

static rt_uint8_t wrtnode2r_spi_stm32_get_write_buf_len(void)
{
    return (rt_uint8_t)rt_ringbuffer_data_len(&spi_bridge.write_buf);
}

static rt_uint8_t wrtnode2r_spi_stm32_get_write_buf_data(void)
{
    rt_uint8_t ch = 0;

    rt_ringbuffer_getchar(&spi_bridge.write_buf, &ch);
    return ch;
}

static rt_uint8_t wrtnode2r_spi_stm32_get_read_buf_len(void)
{
    return (rt_uint8_t)rt_ringbuffer_data_len(&spi_bridge.read_buf);
}

static void wrtnode2r_spi_stm32_set_read_buf_data(rt_uint8_t ch)
{
    rt_ringbuffer_putchar(&spi_bridge.read_buf, ch);
}

static rt_err_t wrtnode2r_spi_bridge_open(rt_device_t dev, rt_uint16_t oflag)
{
    if(!(oflag &RT_DEVICE_FLAG_INT_RX)) {
        return -RT_EIO;
    }

    dev->open_flag = oflag & 0xff;

    rt_ringbuffer_init(&spi_bridge.read_buf, spi_bridge.read_buf_pool, WRTNODE2R_SPI_MAX_DATA_LEN);
    rt_ringbuffer_init(&spi_bridge.write_buf, spi_bridge.write_buf_pool, WRTNODE2R_SPI_MAX_DATA_LEN);
    spi1.beginSlave();

    return RT_EOK;
}

static rt_size_t wrtnode2r_spi_bridge_read(rt_device_t dev,
                                           rt_off_t pos,
                                           void* buffer,
                                           rt_size_t size)
{
    return rt_ringbuffer_get(&spi_bridge.read_buf, buffer, size);
}

static rt_size_t wrtnode2r_spi_bridge_write(rt_device_t dev,
                                            rt_off_t pos,
                                            const void* buffer,
                                            rt_size_t size)
{
    return rt_ringbuffer_put(&spi_bridge.write_buf, buffer, size);
}

void wrtnode2r_spi_bridge_init(const char* name)
{
    /* register device */
    spi_bridge.parent.type           = RT_Device_Class_Miscellaneous;
    spi_bridge.parent.init           = RT_NULL;
    spi_bridge.parent.open           = wrtnode2r_spi_bridge_open;
    spi_bridge.parent.close          = RT_NULL;
    spi_bridge.parent.read           = wrtnode2r_spi_bridge_read;
    spi_bridge.parent.write          = wrtnode2r_spi_bridge_write;
    spi_bridge.parent.control        = RT_NULL;
    /* no private */
    spi_bridge.parent.user_data = RT_NULL;

    rt_device_register(&spi_bridge.parent, name, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STANDALONE);
}

static void wrtnode2r_spi_bridge_rx_isr(rt_uint8_t cmd)
{
    switch(cmd) {
        rt_uint8_t ch = 0;
        case WRTNODE2R_SPI_CMD_GET_STATUS:
            ch = wrtnode2r_spi_stm32_get_status();
            spi1.write(ch);
            break;
        case WRTNODE2R_SPI_CMD_7688_READ_FROM_SRM32_LEN:
            ch = wrtnode2r_spi_stm32_get_write_buf_len();
            spi1.write(ch);
            break;
        case WRTNODE2R_SPI_CMD_7688_WRITE_TO_STM32_LEN:
            ch = spi1.read();
            break;
        case WRTNODE2R_SPI_CMD_7688_READ_FROM_STM32:
            ch = wrtnode2r_spi_stm32_get_write_buf_data();
            spi1.write(ch);
            break;
        case WRTNODE2R_SPI_CMD_7688_WRITE_TO_STM32:
            ch = spi1.read();
            wrtnode2r_spi_stm32_set_read_buf_data(ch);
            if('\n' == ch) {
                if(spi_bridge.parent.rx_indicate != RT_NULL) {
                    spi_bridge.parent.rx_indicate(&spi_bridge.parent, wrtnode2r_spi_stm32_get_read_buf_len());
                }
            }
            break;
        default:
            break;
    }
}

void SPI1_IRQHandler(void) {
    static rt_uint8_t got_cmd;
    static rt_uint8_t cmd;
    rt_interrupt_enter();
    if(spi_is_rx_nonempty(spi1.c_dev())) {
        nvic_irq_disable(NVIC_SPI1);
        if(got_cmd) {
            wrtnode2r_spi_bridge_rx_isr(cmd);
            cmd = 0;
            got_cmd = 0;
        }
        else {
            cmd = spi1.read();
            got_cmd = 1;
        }
        nvic_irq_enable(NVIC_SPI1);
    }
    rt_interrupt_leave();
}

