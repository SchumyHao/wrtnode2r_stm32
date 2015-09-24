/*
 * File      : usart.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2013, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 * 2010-03-29     Bernard      remove interrupt Tx and DMA Rx mode
 * 2013-05-13     aozima       update for kehong-lingtai.
 * 2015-01-31     armink       make sure the serial transmit complete in putc()
 */

#include "wirish/wirish.h"
#include <rtdevice.h>
#include <rthw.h>
#include <rtthread.h>
#include "libmaple/usart.h"

static rt_err_t stm32_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    Serial1.begin(cfg->baud_rate);
    return RT_EOK;
}

static rt_err_t stm32_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    switch (cmd) {
    case RT_DEVICE_CTRL_CLR_INT:
        return RT_EIO;
    case RT_DEVICE_CTRL_SET_INT:
        return RT_EOK;
    }
    return RT_EOK;
}

static int stm32_putc(struct rt_serial_device *serial, char c)
{
    Serial1.write((unsigned char)c);

    return 1;
}

static int stm32_getc(struct rt_serial_device *serial)
{
    RT_ASSERT(RT_NULL != serial);
    int ch = -1;
    struct usart_dev* usart_dev = Serial1.c_dev();

    if (usart_dev->regs->SR & USART_SR_RXNE) {
        ch = usart_dev->regs->DR & 0xff;
    }

    return ch;
}

static const struct rt_uart_ops stm32_uart_ops =
{
    stm32_configure,
    stm32_control,
    stm32_putc,
    stm32_getc,
};

struct rt_serial_device serial1;

void rt_hw_usart_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    config.baud_rate = BAUD_RATE_115200;

    serial1.ops    = &stm32_uart_ops;
    serial1.config = config;

    /* register UART1 device */
    rt_hw_serial_register(&serial1, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          NULL);
}

/*
 * Interrupt handlers.
 */

void USART1_IRQHandler(void) {
    struct usart_dev* usart_dev = Serial1.c_dev();

    rt_interrupt_enter();
    if (usart_dev->regs->SR & USART_SR_RXNE) {
        rt_hw_serial_isr(&serial1, RT_SERIAL_EVENT_RX_IND);
    }
    rt_interrupt_leave();
}

