/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2013, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */

/**
 * @addtogroup STM32
 */
/*@{*/

#include <rtthread.h>
#include <stdint.h>
#include <string.h>

#ifdef RT_USING_FINSH
#include <shell.h>
#include <finsh.h>
#endif

void rt_init_thread_entry(void* parameter)
{
    int ch;

    rt_thread_delay(RT_TICK_PER_SECOND);

    {
        extern void rt_platform_init(void);
        rt_platform_init();
    }
#ifdef RT_USING_FINSH
    /* initialize finsh */
    finsh_system_init();
    finsh_set_device(RT_CONSOLE_DEVICE_NAME);
    rt_thread_delay(10); /* wait finsh thread init OK */
    if(rt_strncmp(RT_CONSOLE_DEVICE_NAME, "bridge", sizeof("bridge")) == 0)
        finsh_set_echo(0);
#endif
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
    rt_show_version();
}

int rt_application_init(void)
{
    rt_thread_t tid;

    tid = rt_thread_create("init",
        rt_init_thread_entry, RT_NULL,
        2048, RT_THREAD_PRIORITY_MAX/3, 20);
    if (tid != RT_NULL) rt_thread_startup(tid);

    return 0;
}

void cmd_2r_version(void)
{
#define __W_VERSION(V) #V
#define W_VERSION(X)   __W_VERSION(X)

    rt_kprintf("%s\n", W_VERSION(WRTNODE2R_VERSION));
}
MSH_CMD_EXPORT_ALIAS(cmd_2r_version, 2r_version, get wrtnode2r stm32 version.);

#include "stm32f10x.h"

#if (__ARMCC_VERSION >= 400000)
#else
extern void __set_PRIMASK(uint32_t priMask);
#endif
extern void __set_PSP(uint32_t topOfProcStack);
void cmd_reset(void)
{
    rt_uint32_t usrAddr = 0x08000000;
    typedef void (*funcPtr)(void);
    typedef volatile uint32_t vu32;
    __set_PRIMASK(0); //关闭所有中断，可以没有
    if(((*(vu32*)usrAddr)&0x2FFE0000)==0x20000000) //判断地址是不是在RAM之内
    {
        rt_uint32_t jumpAddr = *(vu32*) (usrAddr+0x04); /* reset ptr in vector table */
        funcPtr usrMain1 = (funcPtr)jumpAddr;
        __set_PSP(*(vu32*)usrAddr);  //设置堆栈指针
        usrMain1();                                /* go! */
    }
}
MSH_CMD_EXPORT_ALIAS(cmd_reset, reset, reset to bootloader.);
