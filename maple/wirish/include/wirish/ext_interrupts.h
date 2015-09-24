/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

/**
 * @file wirish/include/wirish/ext_interrupts.h
 * @brief Wiring-like external interrupt prototypes and types.
 */

#ifndef _WIRISH_EXT_INTERRUPTS_H_
#define _WIRISH_EXT_INTERRUPTS_H_

#include <libmaple/libmaple_types.h>
#include <libmaple/nvic.h>

/**
 * The kind of transition on an external pin which should trigger an
 * interrupt.
 */
typedef enum ExtIntTriggerMode {
    RISING, /**< To trigger an interrupt when the pin transitions LOW
                 to HIGH */
    FALLING, /**< To trigger an interrupt when the pin transitions
                  HIGH to LOW */
    CHANGE /**< To trigger an interrupt when the pin transitions from
                LOW to HIGH or HIGH to LOW (i.e., when the pin
                changes). */
} ExtIntTriggerMode;

/**
 *  @brief Registers an interrupt handler on a pin.
 *
 *  The interrupt will be triggered on a given transition on the pin,
 *  as specified by the mode parameter.  The handler runs in interrupt
 *  context.  The new handler will replace whatever handler is
 *  currently registered for the pin, if any.
 *
 *  @param pin Pin number
 *  @param handler Function to run upon external interrupt trigger.
 *                 The handler should take no arguments, and have void
 *                 return type.
 *  @param mode Type of transition to trigger on, e.g. falling, rising, etc.
 *
 *  @sideeffect Registers a handler
 *  @see detachInterrupt()
 */
#ifndef MAPLE_USE_WIRISHC
void attachInterrupt(uint8 pin, voidFuncPtr handler, ExtIntTriggerMode mode);
#else /* MAPLE_USE_WIRISHC */
#ifdef  __cplusplus
extern "C" {
#endif /* __cplusplus */
void attachInterrupt(uint8 pin, voidFuncPtr handler, ExtIntTriggerMode mode);
#ifdef  __cplusplus
}
#endif /* __cplusplus */
#endif /* MAPLE_USE_WIRISHC */

/**
 *  @brief Registers an interrupt handler on a pin.
 *
 *  The interrupt will be triggered on a given transition on the pin,
 *  as specified by the mode parameter.  The handler runs in interrupt
 *  context.  The new handler will replace whatever handler is
 *  currently registered for the pin, if any.
 *
 *  @param pin Pin number
 *  @param handler Static class member function to run upon external interrupt
 *                 trigger. The handler should take 1 argument and return void
 *  @param arg Argument that the handler will be passed when it's called. One
 *             use of this is to pass the specific instance of the class that
 *             will handle the interrupt.
 *  @param mode Type of transition to trigger on, e.g. falling, rising, etc.
 *
 *  @sideeffect Registers a handler
 *  @see detachInterrupt()
 */
#ifndef MAPLE_USE_WIRISHC
void attachInterrupt(uint8 pin, voidArgumentFuncPtr handler, void *arg,
                     ExtIntTriggerMode mode);
#else /* MAPLE_USE_WIRISHC */
#ifdef  __cplusplus
extern "C" {
#endif /* __cplusplus */
void attachInterrupt_arg(uint8 pin, voidArgumentFuncPtr handler, void *arg,
                     ExtIntTriggerMode mode);
#ifdef  __cplusplus
}
#endif /* __cplusplus */
#endif /* MAPLE_USE_WIRISHC */

/**
 * @brief Disable any registered external interrupt.
 * @param pin Maple pin number
 * @sideeffect unregisters external interrupt handler
 * @see attachInterrupt()
 */
#ifndef MAPLE_USE_WIRISHC
void detachInterrupt(uint8 pin);
#else /* MAPLE_USE_WIRISHC */
#ifdef  __cplusplus
extern "C" {
#endif /* __cplusplus */
void detachInterrupt(uint8 pin);
#ifdef  __cplusplus
}
#endif /* __cplusplus */
#endif /* MAPLE_USE_WIRISHC */

/**
 * Re-enable interrupts.
 *
 * Call this after noInterrupts() to re-enable interrupt handling,
 * after you have finished with a timing-critical section of code.
 *
 * @see noInterrupts()
 */
#ifndef MAPLE_USE_WIRISHC
static inline void interrupts() {
    nvic_globalirq_enable();
}
#else /* MAPLE_USE_WIRISHC */
#ifdef  __cplusplus
extern "C" {
#endif /* __cplusplus */
static inline void interrupts() {
    nvic_globalirq_enable();
}
#ifdef  __cplusplus
}
#endif /* __cplusplus */
#endif /* MAPLE_USE_WIRISHC */

/**
 * Disable interrupts.
 *
 * After calling this function, all user-programmable interrupts will
 * be disabled.  You can call this function before a timing-critical
 * section of code, then call interrupts() to re-enable interrupt
 * handling.
 *
 * @see interrupts()
 */
#ifndef MAPLE_USE_WIRISHC
static inline void noInterrupts() {
    nvic_globalirq_disable();
}
#else /* MAPLE_USE_WIRISHC */
#ifdef  __cplusplus
extern "C" {
#endif /* __cplusplus */
static inline void noInterrupts() {
    nvic_globalirq_disable();
}
#ifdef  __cplusplus
}
#endif /* __cplusplus */
#endif /* MAPLE_USE_WIRISHC */

#endif

