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

#include "wirish/wirish.h"

int cmd_pinMode(int argc, char** argv)
{
    int pin;
    int mode;
    if(argc == 3) {
        sscanf(argv[1], "%d", &pin);
        if(strcmp(argv[2], "OUTPUT") == 0) {
            mode = OUTPUT;
        }
        else if(strcmp(argv[2], "OUTPUT_OPEN_DRAIN") == 0) {
            mode = OUTPUT_OPEN_DRAIN;
        }
        else if(strcmp(argv[2], "INPUT") == 0) {
            mode = INPUT;
        }
        else if(strcmp(argv[2], "INPUT_ANALOG") == 0) {
            mode = INPUT_ANALOG;
        }
        else if(strcmp(argv[2], "INPUT_PULLUP") == 0) {
            mode = INPUT_PULLUP;
        }
        else if(strcmp(argv[2], "INPUT_PULLDOWN") == 0) {
            mode = INPUT_PULLDOWN;
        }
        else if(strcmp(argv[2], "INPUT_FLOATING") == 0) {
            mode = INPUT_FLOATING;
        }
        else if(strcmp(argv[2], "PWM") == 0) {
            mode = PWM;
        }
        else if(strcmp(argv[2], "PWM_OPEN_DRAIN") == 0) {
            mode = PWM_OPEN_DRAIN;
        }
        else{
            sscanf(argv[2], "%d", &mode);
        }
        pinMode((uint8_t)pin, (int)mode);
    }

    return 0;
}
MSH_CMD_EXPORT_ALIAS(cmd_pinMode, pinMode, pinMode pinNum mode.);

int cmd_digitalRead(int argc, char** argv)
{
    int ret = 0;
    int pin;
    if(argc == 2) {
        sscanf(argv[1], "%d", &pin);
        ret = digitalRead((rt_uint8_t)pin);
    }
    rt_kprintf("%d\n", ret);

    return ret;
}
MSH_CMD_EXPORT_ALIAS(cmd_digitalRead, digitalRead, digitalRead pinNum.);

int cmd_digitalWrite(int argc, char** argv)
{
    int pin;
    int val;
    if(argc == 3) {
        sscanf(argv[1], "%d", &pin);
        if(strcmp(argv[2], "HIGH") == 0) {
            val = HIGH;
        }
        else if(strcmp(argv[2], "LOW") == 0) {
            val = LOW;
        }
        else {
            sscanf(argv[2], "%d", &val);
        }
        digitalWrite((uint8_t)pin, (uint8_t)val);
    }

    return 0;
}
MSH_CMD_EXPORT_ALIAS(cmd_digitalWrite, digitalWrite, digitalWrite pinNum HIGH/LOW.);

int cmd_togglePin(int argc, char** argv)
{
    int pin;
    if(argc == 2) {
        sscanf(argv[1], "%d", &pin);
        togglePin((uint8_t)pin);
    }

    return 0;
}
MSH_CMD_EXPORT_ALIAS(cmd_togglePin, togglePin, togglePin pinNum.);

int cmd_analogRead(int argc, char** argv)
{
    int ret = 0;
    int pin;
	if(argc == 2) {
        sscanf(argv[1], "%d", &pin);
	    ret = analogRead((uint8_t)pin);
	}
    rt_kprintf("%d\n", ret);

	return 0;
}
MSH_CMD_EXPORT_ALIAS(cmd_analogRead, analogRead, analogRead pinNum.);

int cmd_pwmWrite(int argc, char** argv)
{
    int pin;
    int duty_cycle;
    if(argc == 3) {
        sscanf(argv[1], "%d", &pin);
        sscanf(argv[2], "%d", &duty_cycle);
        pwmWrite((uint8_t)pin, (uint16_t)duty_cycle);
    }

    return 0;
}
MSH_CMD_EXPORT_ALIAS(cmd_pwmWrite, pwmWrite, pwmWrite pinNum duty_cycle.);

extern void __set_PRIMASK(uint32_t priMask);
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
