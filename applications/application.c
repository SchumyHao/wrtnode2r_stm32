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
#include "board.h"

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
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
    rt_show_version();
#ifdef RT_USING_FINSH
	/* initialize finsh */
	finsh_system_init();
	finsh_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
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

#if 0
int cmd_digitalRead(int argc, char** argv)
{
    int ret = 0;
    int pin;
    scanf(argv[0], "%d", &pin);
    pin = atoi(argv[0]);

    ret = digitalRead((rt_uint8_t)pin);
    rt_kprintf("%d\n", ret);
}

FINSH_FUNCTION_EXPORT_ALIAS(cmd_digitalRead, __cmd_digitalRead, Read digital pin.);
//FINSH_FUNCTION_EXPORT_ALIAS(cmd_pinMode, __cmd_pinMode, Setup pin mode.);
//FINSH_FUNCTION_EXPORT_ALIAS(cmd_digitalWrite, __cmd_digitalWrite, Write digital pin.);
#endif

#if 0
#include <core_cm3.h>
void cmd_reset(void)
{
    rt_uint32_t usrAddr = 0x08000000;
    typedef void (*funcPtr)(void);
    typedef volatile rt_uint32_t vu32;
    __set_PRIMASK(0); //关闭所有中断，可以没有
    if(((*(vu32*)usrAddr)&0x2FFE0000)==0x20000000) //判断地址是不是在RAM之内
    {
        rt_uint32_t jumpAddr = *(vu32*) (usrAddr+0x04); /* reset ptr in vector table */
        funcPtr usrMain1 = (funcPtr)jumpAddr;
        __set_PSP(*(vu32*)usrAddr);  //设置堆栈指针
        usrMain1();                                /* go! */
    }
}
#else
extern _edata;
#define STACK_TOP _edata
#define EXC_RETURN 0xFFFFFFF9
#define DEFAULT_CPSR 0x61000000
#define RESET_DELAY 100000
static void wait_reset(void) {
  rt_thread_delay(RESET_DELAY/RT_TICK_PER_SECOND);
  nvic_sys_reset();
}

void cmd_reset(void)
{
            // Got the magic sequence -> reset, presumably into the bootloader.
            // Return address is wait_reset, but we must set the thumb bit.
						//TODO: Fix it
            uintptr_t target = (uintptr_t)wait_reset | 0x1;
            asm volatile("mov r0, %[stack_top]      \n\t" // Reset stack
                         "mov sp, r0                \n\t"
                         "mov r0, #1                \n\t"
                         "mov r1, %[target_addr]    \n\t"
                         "mov r2, %[cpsr]           \n\t"
                         "push {r2}                 \n\t" // Fake xPSR
                         "push {r1}                 \n\t" // PC target addr
                         "push {r0}                 \n\t" // Fake LR
                         "push {r0}                 \n\t" // Fake R12
                         "push {r0}                 \n\t" // Fake R3
                         "push {r0}                 \n\t" // Fake R2
                         "push {r0}                 \n\t" // Fake R1
                         "push {r0}                 \n\t" // Fake R0
                         "mov lr, %[exc_return]     \n\t"
                         "bx lr"
                         :
                         : [stack_top] "r" (STACK_TOP),
                           [target_addr] "r" (target),
                           [exc_return] "r" (EXC_RETURN),
                           [cpsr] "r" (DEFAULT_CPSR)
                         : "r0", "r1", "r2");
}
#endif

FINSH_FUNCTION_EXPORT_ALIAS(cmd_reset, __cmd_reset, reset to bootloader.);
