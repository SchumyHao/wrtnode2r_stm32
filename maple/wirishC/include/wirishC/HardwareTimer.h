#ifndef _WIRISHC_HARDWARETIMER_H_
#define _WIRISHC_HARDWARETIMER_H_

// TODO [0.1.0] Remove deprecated pieces, pick a better API

#include <libmaple/timer.h>

#ifdef __cplusplus
extern "C" {
#endif

struct HardwareTimer_t {
    void (*pause)(void);
    void (*resume)(void);
    uint32 (*getPrescaleFactor)(void);
    void (*setPrescaleFactor)(uint32 factor);
    uint16 (*getOverflow)(void);
    void (*setOverflow)(uint16 val);
    uint16 (*getCount)(void);
    void (*setCount)(uint16 val);
    uint16 (*setPeriod)(uint32 microseconds);
    void (*setMode)(int channel, timer_mode mode);
    uint16 (*getCompare)(int channel);
    void (*setCompare)(int channel, uint16 compare);
    void (*attachInterrupt)(int channel, voidFuncPtr handler);
    void (*detachInterrupt)(int channel);
    void (*refresh)(void);
    timer_dev* (*c_dev)(void);
};

extern struct HardwareTimer_t Timer1;
extern struct HardwareTimer_t Timer2;
extern struct HardwareTimer_t Timer3;
extern struct HardwareTimer_t Timer4;
#if (STM32_MCU_SERIES == STM32_SERIES_F1) && defined(STM32_HIGH_DENSITY)
extern struct HardwareTimer_t Timer5;
extern struct HardwareTimer_t Timer8;
#endif

#ifdef __cplusplus
}
#endif

#endif
