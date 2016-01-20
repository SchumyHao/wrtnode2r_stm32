/*
 * File      : board.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2013, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-09-22     Bernard      add board.h to this bsp
 * 2015-12-06     Schumy       WRTnode2R board
 */

// <<< Use Configuration Wizard in Context Menu >>>
#ifndef __WRTNODE2R_BOARD_H__
#define __WRTNODE2R_BOARD_H__

#include <stdbool.h>

void rt_hw_board_init(void);
//void rt_hw_usart_init(void);
void spi_bridge_register(const char* name);

#define STM32_SRAM_SIZE         20
#define STM32_SRAM_END          (0x20000000 + STM32_SRAM_SIZE * 1024)

#endif
