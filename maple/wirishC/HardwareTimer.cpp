#include <wirish/HardwareTimer.h>

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

/* -- Deprecated predefined instances -------------------------------------- */

#if STM32_TIMER_MASK & (1 << 1)
static HardwareTimer CPP_TIMER1(1);
#endif
#if STM32_TIMER_MASK & (1 << 2)
static HardwareTimer CPP_TIMER2(2);
#endif
#if STM32_TIMER_MASK & (1 << 3)
static HardwareTimer CPP_TIMER3(3);
#endif
#if STM32_TIMER_MASK & (1 << 4)
static HardwareTimer CPP_TIMER4(4);
#endif
#if (STM32_MCU_SERIES == STM32_SERIES_F1) && defined(STM32_HIGH_DENSITY)
#if STM32_TIMER_MASK & (1 << 5)
static HardwareTimer CPP_TIMER5(5);
#endif
#if STM32_TIMER_MASK & (1 << 6)
static HardwareTimer CPP_TIMER6(6);
#endif
#if STM32_TIMER_MASK & (1 << 7)
static HardwareTimer CPP_TIMER7(7);
#endif
#if STM32_TIMER_MASK & (1 << 8)
static HardwareTimer CPP_TIMER8(8);
#endif
#endif

extern "C" {
    static void pause(uint8 timerNum)
    {
        switch (timerNum) {
#if STM32_TIMER_MASK & (1 << 1)
            case 1:
                CPP_TIMER1.pause();
                break;
#endif
#if STM32_TIMER_MASK & (1 << 2)
            case 2:
                CPP_TIMER2.pause();
                break;
#endif
#if STM32_TIMER_MASK & (1 << 3)
            case 3:
                CPP_TIMER3.pause();
                break;
#endif
#if STM32_TIMER_MASK & (1 << 4)
            case 4:
                CPP_TIMER4.pause();
                break;
#endif
#if (STM32_MCU_SERIES == STM32_SERIES_F1) && defined(STM32_HIGH_DENSITY)
#if STM32_TIMER_MASK & (1 << 5)
            case 5:
                CPP_TIMER5.pause();
                break;
#endif
#if STM32_TIMER_MASK & (1 << 6)
            case 6:
                CPP_TIMER6.pause();
                break;
#endif
#if STM32_TIMER_MASK & (1 << 7)
            case 7:
                CPP_TIMER7.pause();
                break;
#endif
#if STM32_TIMER_MASK & (1 << 8)
            case 8:
                CPP_TIMER8.pause();
                break;
#endif
#endif
            default:
                ASSERT(0);
        }
    }

    static void resume(uint8 timerNum)
    {
        switch (timerNum) {
#if STM32_TIMER_MASK & (1 << 1)
            case 1:
                CPP_TIMER1.resume();
                break;
#endif
#if STM32_TIMER_MASK & (1 << 2)
            case 2:
                CPP_TIMER2.resume();
                break;
#endif
#if STM32_TIMER_MASK & (1 << 3)
            case 3:
                CPP_TIMER3.resume();
                break;
#endif
#if STM32_TIMER_MASK & (1 << 4)
            case 4:
                CPP_TIMER4.resume();
                break;
#endif
#if (STM32_MCU_SERIES == STM32_SERIES_F1) && defined(STM32_HIGH_DENSITY)
#if STM32_TIMER_MASK & (1 << 5)
            case 5:
                CPP_TIMER5.resume();
                break;
#endif
#if STM32_TIMER_MASK & (1 << 6)
            case 6:
                CPP_TIMER6.resume();
                break;
#endif
#if STM32_TIMER_MASK & (1 << 7)
            case 7:
                CPP_TIMER7.resume();
                break;
#endif
#if STM32_TIMER_MASK & (1 << 8)
            case 8:
                CPP_TIMER8.resume();
                break;
#endif
#endif
            default:
                ASSERT(0);
        }
    }

    static uint32 getPrescaleFactor(uint8 timerNum)
    {
        switch (timerNum) {
#if STM32_TIMER_MASK & (1 << 1)
            case 1:
                return CPP_TIMER1.getPrescaleFactor();
#endif
#if STM32_TIMER_MASK & (1 << 2)
            case 2:
                return CPP_TIMER2.getPrescaleFactor();
#endif
#if STM32_TIMER_MASK & (1 << 3)
            case 3:
                return CPP_TIMER3.getPrescaleFactor();
#endif
#if STM32_TIMER_MASK & (1 << 4)
            case 4:
                return CPP_TIMER4.getPrescaleFactor();
#endif
#if (STM32_MCU_SERIES == STM32_SERIES_F1) && defined(STM32_HIGH_DENSITY)
#if STM32_TIMER_MASK & (1 << 5)
            case 5:
                return CPP_TIMER5.getPrescaleFactor();
#endif
#if STM32_TIMER_MASK & (1 << 6)
            case 6:
                return CPP_TIMER6.getPrescaleFactor();
#endif
#if STM32_TIMER_MASK & (1 << 7)
            case 7:
                return CPP_TIMER7.getPrescaleFactor();
#endif
#if STM32_TIMER_MASK & (1 << 8)
            case 8:
                return CPP_TIMER8.getPrescaleFactor();
#endif
#endif
            default:
                ASSERT(0);
        }
        return 0;
    }

    static void setPrescaleFactor(uint8 timerNum, uint32 factor)
    {
        switch (timerNum) {
#if STM32_TIMER_MASK & (1 << 1)
            case 1:
                CPP_TIMER1.setPrescaleFactor(factor);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 2)
            case 2:
                CPP_TIMER2.setPrescaleFactor(factor);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 3)
            case 3:
                CPP_TIMER3.setPrescaleFactor(factor);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 4)
            case 4:
                CPP_TIMER4.setPrescaleFactor(factor);
                break;
#endif
#if (STM32_MCU_SERIES == STM32_SERIES_F1) && defined(STM32_HIGH_DENSITY)
#if STM32_TIMER_MASK & (1 << 5)
            case 5:
                CPP_TIMER5.setPrescaleFactor(factor);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 6)
            case 6:
                CPP_TIMER6.setPrescaleFactor(factor);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 7)
            case 7:
                CPP_TIMER7.setPrescaleFactor(factor);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 8)
            case 8:
                CPP_TIMER8.setPrescaleFactor(factor);
                break;
#endif
#endif
            default:
                ASSERT(0);
        }
    }

    static uint16 getOverflow(uint8 timerNum)
    {
        switch (timerNum) {
#if STM32_TIMER_MASK & (1 << 1)
            case 1:
                return CPP_TIMER1.getOverflow();
#endif
#if STM32_TIMER_MASK & (1 << 2)
            case 2:
                return CPP_TIMER2.getOverflow();
#endif
#if STM32_TIMER_MASK & (1 << 3)
            case 3:
                return CPP_TIMER3.getOverflow();
#endif
#if STM32_TIMER_MASK & (1 << 4)
            case 4:
                return CPP_TIMER4.getOverflow();
#endif
#if (STM32_MCU_SERIES == STM32_SERIES_F1) && defined(STM32_HIGH_DENSITY)
#if STM32_TIMER_MASK & (1 << 5)
            case 5:
                return CPP_TIMER5.getOverflow();
#endif
#if STM32_TIMER_MASK & (1 << 6)
            case 6:
                return CPP_TIMER6.getOverflow();
#endif
#if STM32_TIMER_MASK & (1 << 7)
            case 7:
                return CPP_TIMER7.getOverflow();
#endif
#if STM32_TIMER_MASK & (1 << 8)
            case 8:
                return CPP_TIMER8.getOverflow();
#endif
#endif
            default:
                ASSERT(0);
        }
        return 0;
    }

    static void setOverflow(uint8 timerNum, uint16 val)
    {
        switch (timerNum) {
#if STM32_TIMER_MASK & (1 << 1)
            case 1:
                CPP_TIMER1.setOverflow(val);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 2)
            case 2:
                CPP_TIMER2.setOverflow(val);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 3)
            case 3:
                CPP_TIMER3.setOverflow(val);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 4)
            case 4:
                CPP_TIMER4.setOverflow(val);
                break;
#endif
#if (STM32_MCU_SERIES == STM32_SERIES_F1) && defined(STM32_HIGH_DENSITY)
#if STM32_TIMER_MASK & (1 << 5)
            case 5:
                CPP_TIMER5.setOverflow(val);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 6)
            case 6:
                CPP_TIMER6.setOverflow(val);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 7)
            case 7:
                CPP_TIMER7.setOverflow(val);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 8)
            case 8:
                CPP_TIMER8.setOverflow(val);
                break;
#endif
#endif
            default:
                ASSERT(0);
        }
    }

    static uint16 getCount(uint8 timerNum)
    {
        switch (timerNum) {
#if STM32_TIMER_MASK & (1 << 1)
            case 1:
                return CPP_TIMER1.getCount();
#endif
#if STM32_TIMER_MASK & (1 << 2)
            case 2:
                return CPP_TIMER2.getCount();
#endif
#if STM32_TIMER_MASK & (1 << 3)
            case 3:
                return CPP_TIMER3.getCount();
#endif
#if STM32_TIMER_MASK & (1 << 4)
            case 4:
                return CPP_TIMER4.getCount();
#endif
#if (STM32_MCU_SERIES == STM32_SERIES_F1) && defined(STM32_HIGH_DENSITY)
#if STM32_TIMER_MASK & (1 << 5)
            case 5:
                return CPP_TIMER5.getCount();
#endif
#if STM32_TIMER_MASK & (1 << 6)
            case 6:
                return CPP_TIMER6.getCount();
#endif
#if STM32_TIMER_MASK & (1 << 7)
            case 7:
                return CPP_TIMER7.getCount();
#endif
#if STM32_TIMER_MASK & (1 << 8)
            case 8:
                return CPP_TIMER8.getCount();
#endif
#endif
            default:
                ASSERT(0);
        }
        return 0;
    }

    static void setCount(uint8 timerNum, uint16 val)
    {
        switch (timerNum) {
#if STM32_TIMER_MASK & (1 << 1)
            case 1:
                CPP_TIMER1.setCount(val);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 2)
            case 2:
                CPP_TIMER2.setCount(val);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 3)
            case 3:
                CPP_TIMER3.setCount(val);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 4)
            case 4:
                CPP_TIMER4.setCount(val);
                break;
#endif
#if (STM32_MCU_SERIES == STM32_SERIES_F1) && defined(STM32_HIGH_DENSITY)
#if STM32_TIMER_MASK & (1 << 5)
            case 5:
                CPP_TIMER5.setCount(val);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 6)
            case 6:
                CPP_TIMER6.setCount(val);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 7)
            case 7:
                CPP_TIMER7.setCount(val);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 8)
            case 8:
                CPP_TIMER8.setCount(val);
                break;
#endif
#endif
            default:
                ASSERT(0);
        }
    }

    static uint16 setPeriod(uint8 timerNum, uint32 microseconds)
    {
        switch (timerNum) {
#if STM32_TIMER_MASK & (1 << 1)
            case 1:
                return CPP_TIMER1.setPeriod(microseconds);
#endif
#if STM32_TIMER_MASK & (1 << 2)
            case 2:
                return CPP_TIMER2.setPeriod(microseconds);
#endif
#if STM32_TIMER_MASK & (1 << 3)
            case 3:
                return CPP_TIMER3.setPeriod(microseconds);
#endif
#if STM32_TIMER_MASK & (1 << 4)
            case 4:
                return CPP_TIMER4.setPeriod(microseconds);
#endif
#if (STM32_MCU_SERIES == STM32_SERIES_F1) && defined(STM32_HIGH_DENSITY)
#if STM32_TIMER_MASK & (1 << 5)
            case 5:
                return CPP_TIMER5.setPeriod(microseconds);
#endif
#if STM32_TIMER_MASK & (1 << 6)
            case 6:
                return CPP_TIMER6.setPeriod(microseconds);
#endif
#if STM32_TIMER_MASK & (1 << 7)
            case 7:
                return CPP_TIMER7.setPeriod(microseconds);
#endif
#if STM32_TIMER_MASK & (1 << 8)
            case 8:
                return CPP_TIMER8.setPeriod(microseconds);
#endif
#endif
            default:
                ASSERT(0);
        }
        return 0;
    }

    static void setMode(uint8 timerNum, int channel, timer_mode mode)
    {
        switch (timerNum) {
#if STM32_TIMER_MASK & (1 << 1)
            case 1:
                CPP_TIMER1.setMode(channel, mode);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 2)
            case 2:
                CPP_TIMER2.setMode(channel, mode);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 3)
            case 3:
                CPP_TIMER3.setMode(channel, mode);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 4)
            case 4:
                CPP_TIMER4.setMode(channel, mode);
                break;
#endif
#if (STM32_MCU_SERIES == STM32_SERIES_F1) && defined(STM32_HIGH_DENSITY)
#if STM32_TIMER_MASK & (1 << 5)
            case 5:
                CPP_TIMER5.setMode(channel, mode);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 6)
            case 6:
                CPP_TIMER6.setMode(channel, mode);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 7)
            case 7:
                CPP_TIMER7.setMode(channel, mode);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 8)
            case 8:
                CPP_TIMER8.setMode(channel, mode);
                break;
#endif
#endif
            default:
                ASSERT(0);
        }
    }

    static uint16 getCompare(uint8 timerNum, int channel)
    {
        switch (timerNum) {
#if STM32_TIMER_MASK & (1 << 1)
            case 1:
                return CPP_TIMER1.getCompare(channel);
#endif
#if STM32_TIMER_MASK & (1 << 2)
            case 2:
                return CPP_TIMER2.getCompare(channel);
#endif
#if STM32_TIMER_MASK & (1 << 3)
            case 3:
                return CPP_TIMER3.getCompare(channel);
#endif
#if STM32_TIMER_MASK & (1 << 4)
            case 4:
                return CPP_TIMER4.getCompare(channel);
#endif
#if (STM32_MCU_SERIES == STM32_SERIES_F1) && defined(STM32_HIGH_DENSITY)
#if STM32_TIMER_MASK & (1 << 5)
            case 5:
                return CPP_TIMER5.getCompare(channel);
#endif
#if STM32_TIMER_MASK & (1 << 6)
            case 6:
                return CPP_TIMER6.getCompare(channel);
#endif
#if STM32_TIMER_MASK & (1 << 7)
            case 7:
                return CPP_TIMER7.getCompare(channel);
#endif
#if STM32_TIMER_MASK & (1 << 8)
            case 8:
                return CPP_TIMER8.getCompare(channel);
#endif
#endif
            default:
                ASSERT(0);
        }
        return 0;
    }

    static void setCompare(uint8 timerNum, int channel, uint16 compare)
    {
        switch (timerNum) {
#if STM32_TIMER_MASK & (1 << 1)
            case 1:
                CPP_TIMER1.setCompare(channel, compare);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 2)
            case 2:
                CPP_TIMER2.setCompare(channel, compare);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 3)
            case 3:
                CPP_TIMER3.setCompare(channel, compare);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 4)
            case 4:
                CPP_TIMER4.setCompare(channel, compare);
                break;
#endif
#if (STM32_MCU_SERIES == STM32_SERIES_F1) && defined(STM32_HIGH_DENSITY)
#if STM32_TIMER_MASK & (1 << 5)
            case 5:
                CPP_TIMER5.setCompare(channel, compare);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 6)
            case 6:
                CPP_TIMER6.setCompare(channel, compare);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 7)
            case 7:
                CPP_TIMER7.setCompare(channel, compare);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 8)
            case 8:
                CPP_TIMER8.setCompare(channel, compare);
                break;
#endif
#endif
            default:
                ASSERT(0);
        }
    }

    static void attachInterrupt(uint8 timerNum, int channel, voidFuncPtr handler)
    {
        switch (timerNum) {
#if STM32_TIMER_MASK & (1 << 1)
            case 1:
                CPP_TIMER1.attachInterrupt(channel, handler);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 2)
            case 2:
                CPP_TIMER2.attachInterrupt(channel, handler);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 3)
            case 3:
                CPP_TIMER3.attachInterrupt(channel, handler);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 4)
            case 4:
                CPP_TIMER4.attachInterrupt(channel, handler);
                break;
#endif
#if (STM32_MCU_SERIES == STM32_SERIES_F1) && defined(STM32_HIGH_DENSITY)
#if STM32_TIMER_MASK & (1 << 5)
            case 5:
                CPP_TIMER5.attachInterrupt(channel, handler);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 6)
            case 6:
                CPP_TIMER6.attachInterrupt(channel, handler);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 7)
            case 7:
                CPP_TIMER7.attachInterrupt(channel, handler);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 8)
            case 8:
                CPP_TIMER8.attachInterrupt(channel, handler);
                break;
#endif
#endif
            default:
                ASSERT(0);
        }
    }

    static void detachInterrupt(uint8 timerNum, int channel)
    {
        switch (timerNum) {
#if STM32_TIMER_MASK & (1 << 1)
            case 1:
                CPP_TIMER1.detachInterrupt(channel);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 2)
            case 2:
                CPP_TIMER2.detachInterrupt(channel);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 3)
            case 3:
                CPP_TIMER3.detachInterrupt(channel);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 4)
            case 4:
                CPP_TIMER4.detachInterrupt(channel);
                break;
#endif
#if (STM32_MCU_SERIES == STM32_SERIES_F1) && defined(STM32_HIGH_DENSITY)
#if STM32_TIMER_MASK & (1 << 5)
            case 5:
                CPP_TIMER5.detachInterrupt(channel);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 6)
            case 6:
                CPP_TIMER6.detachInterrupt(channel);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 7)
            case 7:
                CPP_TIMER7.detachInterrupt(channel);
                break;
#endif
#if STM32_TIMER_MASK & (1 << 8)
            case 8:
                CPP_TIMER8.detachInterrupt(channel);
                break;
#endif
#endif
            default:
                ASSERT(0);
        }
    }

    static void refresh(uint8 timerNum)
    {
        switch (timerNum) {
#if STM32_TIMER_MASK & (1 << 1)
            case 1:
                CPP_TIMER1.refresh();
                break;
#endif
#if STM32_TIMER_MASK & (1 << 2)
            case 2:
                CPP_TIMER2.refresh();
                break;
#endif
#if STM32_TIMER_MASK & (1 << 3)
            case 3:
                CPP_TIMER3.refresh();
                break;
#endif
#if STM32_TIMER_MASK & (1 << 4)
            case 4:
                CPP_TIMER4.refresh();
                break;
#endif
#if (STM32_MCU_SERIES == STM32_SERIES_F1) && defined(STM32_HIGH_DENSITY)
#if STM32_TIMER_MASK & (1 << 5)
            case 5:
                CPP_TIMER5.refresh();
                break;
#endif
#if STM32_TIMER_MASK & (1 << 6)
            case 6:
                CPP_TIMER6.refresh();
                break;
#endif
#if STM32_TIMER_MASK & (1 << 7)
            case 7:
                CPP_TIMER7.refresh();
                break;
#endif
#if STM32_TIMER_MASK & (1 << 8)
            case 8:
                CPP_TIMER8.refresh();
                break;
#endif
#endif
            default:
                ASSERT(0);
        }
    }

    static timer_dev* c_dev(uint8 timerNum)
    {
        switch (timerNum) {
#if STM32_TIMER_MASK & (1 << 1)
            case 1:
                return CPP_TIMER1.c_dev();
#endif
#if STM32_TIMER_MASK & (1 << 2)
            case 2:
                return CPP_TIMER2.c_dev();
#endif
#if STM32_TIMER_MASK & (1 << 3)
            case 3:
                return CPP_TIMER3.c_dev();
#endif
#if STM32_TIMER_MASK & (1 << 4)
            case 4:
                return CPP_TIMER4.c_dev();
#endif
#if (STM32_MCU_SERIES == STM32_SERIES_F1) && defined(STM32_HIGH_DENSITY)
#if STM32_TIMER_MASK & (1 << 5)
            case 5:
                return CPP_TIMER5.c_dev();
#endif
#if STM32_TIMER_MASK & (1 << 6)
            case 6:
                return CPP_TIMER6.c_dev();
#endif
#if STM32_TIMER_MASK & (1 << 7)
            case 7:
                return CPP_TIMER7.c_dev();
#endif
#if STM32_TIMER_MASK & (1 << 8)
            case 8:
                return CPP_TIMER8.c_dev();
#endif
#endif
            default:
                ASSERT(0);
        }
        return NULL;
    }
}

#if STM32_TIMER_MASK & (1 << 1)
extern "C" {
    static inline void pause1(void)
    {
        pause(1);
    }
    static inline void resume1(void)
    {
        resume(1);
    }
    static inline uint32 getPrescaleFactor1(void)
    {
        return getPrescaleFactor(1);
    }
    static inline void setPrescaleFactor1(uint32 factor)
    {
        setPrescaleFactor(1, factor);
    }
    static inline uint16 getOverflow1(void)
    {
        return getOverflow(1);
    }
    static inline void setOverflow1(uint16 val)
    {
        setOverflow(1, val);
    }
    static inline uint16 getCount1(void)
    {
        return getCount(1);
    }
    static inline void setCount1(uint16 val)
    {
        setCount(1, val);
    }
    static inline uint16 setPeriod1(uint32 microseconds)
    {
        return setPeriod(1, microseconds);
    }
    static inline void setMode1(int channel, timer_mode mode)
    {
        setMode(1, channel, mode);
    }
    static inline uint16 getCompare1(int channel)
    {
        return getCompare(1, channel);
    }
    static inline void setCompare1(int channel, uint16 compare)
    {
        setCompare(1, channel, compare);
    }
    static inline void attachInterrupt1(int channel, voidFuncPtr handler)
    {
        attachInterrupt(1, channel, handler);
    }
    static inline void detachInterrupt1(int channel)
    {
        detachInterrupt(1, channel);
    }
    static inline void refresh1(void)
    {
        refresh(1);
    }
    static inline timer_dev* c_dev1(void)
    {
        return c_dev(1);
    }
}

struct HardwareTimer_t Timer1 = {
    pause1,
    resume1,
    getPrescaleFactor1,
    setPrescaleFactor1,
    getOverflow1,
    setOverflow1,
    getCount1,
    setCount1,
    setPeriod1,
    setMode1,
    getCompare1,
    setCompare1,
    attachInterrupt1,
    detachInterrupt1,
    refresh1,
    c_dev1,
};
#endif /*STM32_TIMER_MASK & (1 << 1)*/

#if STM32_TIMER_MASK & (1 << 2)
extern "C" {
    static inline void pause2(void)
    {
        pause(2);
    }
    static inline void resume2(void)
    {
        resume(2);
    }
    static inline uint32 getPrescaleFactor2(void)
    {
        return getPrescaleFactor(2);
    }
    static inline void setPrescaleFactor2(uint32 factor)
    {
        setPrescaleFactor(2, factor);
    }
    static inline uint16 getOverflow2(void)
    {
        return getOverflow(2);
    }
    static inline void setOverflow2(uint16 val)
    {
        setOverflow(2, val);
    }
    static inline uint16 getCount2(void)
    {
        return getCount(2);
    }
    static inline void setCount2(uint16 val)
    {
        setCount(2, val);
    }
    static inline uint16 setPeriod2(uint32 microseconds)
    {
        return setPeriod(2, microseconds);
    }
    static inline void setMode2(int channel, timer_mode mode)
    {
        setMode(2, channel, mode);
    }
    static inline uint16 getCompare2(int channel)
    {
        return getCompare(2, channel);
    }
    static inline void setCompare2(int channel, uint16 compare)
    {
        setCompare(2, channel, compare);
    }
    static inline void attachInterrupt2(int channel, voidFuncPtr handler)
    {
        attachInterrupt(2, channel, handler);
    }
    static inline void detachInterrupt2(int channel)
    {
        detachInterrupt(2, channel);
    }
    static inline void refresh2(void)
    {
        refresh(2);
    }
    static inline timer_dev* c_dev2(void)
    {
        return c_dev(2);
    }
}

struct HardwareTimer_t Timer2 = {
    pause2,
    resume2,
    getPrescaleFactor2,
    setPrescaleFactor2,
    getOverflow2,
    setOverflow2,
    getCount2,
    setCount2,
    setPeriod2,
    setMode2,
    getCompare2,
    setCompare2,
    attachInterrupt2,
    detachInterrupt2,
    refresh2,
    c_dev2,
};
#endif /*STM32_TIMER_MASK & (1 << 2)*/

#if STM32_TIMER_MASK & (1 << 3)
extern "C" {
    static inline void pause3(void)
    {
        pause(3);
    }
    static inline void resume3(void)
    {
        resume(3);
    }
    static inline uint32 getPrescaleFactor3(void)
    {
        return getPrescaleFactor(3);
    }
    static inline void setPrescaleFactor3(uint32 factor)
    {
        setPrescaleFactor(3, factor);
    }
    static inline uint16 getOverflow3(void)
    {
        return getOverflow(3);
    }
    static inline void setOverflow3(uint16 val)
    {
        setOverflow(3, val);
    }
    static inline uint16 getCount3(void)
    {
        return getCount(3);
    }
    static inline void setCount3(uint16 val)
    {
        setCount(3, val);
    }
    static inline uint16 setPeriod3(uint32 microseconds)
    {
        return setPeriod(3, microseconds);
    }
    static inline void setMode3(int channel, timer_mode mode)
    {
        setMode(3, channel, mode);
    }
    static inline uint16 getCompare3(int channel)
    {
        return getCompare(3, channel);
    }
    static inline void setCompare3(int channel, uint16 compare)
    {
        setCompare(3, channel, compare);
    }
    static inline void attachInterrupt3(int channel, voidFuncPtr handler)
    {
        attachInterrupt(3, channel, handler);
    }
    static inline void detachInterrupt3(int channel)
    {
        detachInterrupt(3, channel);
    }
    static inline void refresh3(void)
    {
        refresh(3);
    }
    static inline timer_dev* c_dev3(void)
    {
        return c_dev(3);
    }
}

struct HardwareTimer_t Timer3 = {
    pause3,
    resume3,
    getPrescaleFactor3,
    setPrescaleFactor3,
    getOverflow3,
    setOverflow3,
    getCount3,
    setCount3,
    setPeriod3,
    setMode3,
    getCompare3,
    setCompare3,
    attachInterrupt3,
    detachInterrupt3,
    refresh3,
    c_dev3,
};
#endif /*STM32_TIMER_MASK & (1 << 3)*/

#if STM32_TIMER_MASK & (1 << 4)
extern "C" {
    static inline void pause4(void)
    {
        pause(4);
    }
    static inline void resume4(void)
    {
        resume(4);
    }
    static inline uint32 getPrescaleFactor4(void)
    {
        return getPrescaleFactor(4);
    }
    static inline void setPrescaleFactor4(uint32 factor)
    {
        setPrescaleFactor(4, factor);
    }
    static inline uint16 getOverflow4(void)
    {
        return getOverflow(4);
    }
    static inline void setOverflow4(uint16 val)
    {
        setOverflow(4, val);
    }
    static inline uint16 getCount4(void)
    {
        return getCount(4);
    }
    static inline void setCount4(uint16 val)
    {
        setCount(4, val);
    }
    static inline uint16 setPeriod4(uint32 microseconds)
    {
        return setPeriod(4, microseconds);
    }
    static inline void setMode4(int channel, timer_mode mode)
    {
        setMode(4, channel, mode);
    }
    static inline uint16 getCompare4(int channel)
    {
        return getCompare(4, channel);
    }
    static inline void setCompare4(int channel, uint16 compare)
    {
        setCompare(4, channel, compare);
    }
    static inline void attachInterrupt4(int channel, voidFuncPtr handler)
    {
        attachInterrupt(4, channel, handler);
    }
    static inline void detachInterrupt4(int channel)
    {
        detachInterrupt(4, channel);
    }
    static inline void refresh4(void)
    {
        refresh(4);
    }
    static inline timer_dev* c_dev4(void)
    {
        return c_dev(4);
    }
}

struct HardwareTimer_t Timer4 = {
    pause4,
    resume4,
    getPrescaleFactor4,
    setPrescaleFactor4,
    getOverflow4,
    setOverflow4,
    getCount4,
    setCount4,
    setPeriod4,
    setMode4,
    getCompare4,
    setCompare4,
    attachInterrupt4,
    detachInterrupt4,
    refresh4,
    c_dev4,
};
#endif /*STM32_TIMER_MASK & (1 << 4)*/

#if (STM32_MCU_SERIES == STM32_SERIES_F1) && defined(STM32_HIGH_DENSITY)
#if STM32_TIMER_MASK & (1 << 5)
extern "C" {
    static inline void pause5(void)
    {
        pause(5);
    }
    static inline void resume5(void)
    {
        resume(5);
    }
    static inline uint32 getPrescaleFactor5(void)
    {
        return getPrescaleFactor(5);
    }
    static inline void setPrescaleFactor5(uint32 factor)
    {
        setPrescaleFactor(5, factor);
    }
    static inline uint16 getOverflow5(void)
    {
        return getOverflow(5);
    }
    static inline void setOverflow5(uint16 val)
    {
        setOverflow(5, val);
    }
    static inline uint16 getCount5(void)
    {
        return getCount(5);
    }
    static inline void setCount5(uint16 val)
    {
        setCount(5, val);
    }
    static inline uint16 setPeriod5(uint32 microseconds)
    {
        return setPeriod(5, microseconds);
    }
    static inline void setMode5(int channel, timer_mode mode)
    {
        setMode(5, channel, mode);
    }
    static inline uint16 getCompare5(int channel)
    {
        return getCompare(5, channel);
    }
    static inline void setCompare5(int channel, uint16 compare)
    {
        setCompare(5, channel, compare);
    }
    static inline void attachInterrupt5(int channel, voidFuncPtr handler)
    {
        attachInterrupt(5, channel, handler);
    }
    static inline void detachInterrupt5(int channel)
    {
        detachInterrupt(5, channel);
    }
    static inline void refresh5(void)
    {
        refresh(5);
    }
    static inline timer_dev* c_dev5(void)
    {
        return c_dev(5);
    }
}

struct HardwareTimer_t Timer5 = {
    pause5,
    resume5,
    getPrescaleFactor5,
    setPrescaleFactor5,
    getOverflow5,
    setOverflow5,
    getCount5,
    setCount5,
    setPeriod5,
    setMode5,
    getCompare5,
    setCompare5,
    attachInterrupt5,
    detachInterrupt5,
    refresh5,
    c_dev5,
};
#endif /*STM32_TIMER_MASK & (1 << 5)*/

#if STM32_TIMER_MASK & (1 << 6)
extern "C" {
    static inline void pause6(void)
    {
        pause(6);
    }
    static inline void resume6(void)
    {
        resume(6);
    }
    static inline uint32 getPrescaleFactor6(void)
    {
        return getPrescaleFactor(6);
    }
    static inline void setPrescaleFactor6(uint32 factor)
    {
        setPrescaleFactor(6, factor);
    }
    static inline uint16 getOverflow6(void)
    {
        return getOverflow(6);
    }
    static inline void setOverflow6(uint16 val)
    {
        setOverflow(6, val);
    }
    static inline uint16 getCount6(void)
    {
        return getCount(6);
    }
    static inline void setCount6(uint16 val)
    {
        setCount(6, val);
    }
    static inline uint16 setPeriod6(uint32 microseconds)
    {
        return setPeriod(6, microseconds);
    }
    static inline void setMode6(int channel, timer_mode mode)
    {
        setMode(6, channel, mode);
    }
    static inline uint16 getCompare6(int channel)
    {
        return getCompare(6, channel);
    }
    static inline void setCompare6(int channel, uint16 compare)
    {
        setCompare(6, channel, compare);
    }
    static inline void attachInterrupt6(int channel, voidFuncPtr handler)
    {
        attachInterrupt(6, channel, handler);
    }
    static inline void detachInterrupt6(int channel)
    {
        detachInterrupt(6, channel);
    }
    static inline void refresh6(void)
    {
        refresh(6);
    }
    static inline timer_dev* c_dev6(void)
    {
        return c_dev(6);
    }
}

struct HardwareTimer_t Timer6 = {
    pause6,
    resume6,
    getPrescaleFactor6,
    setPrescaleFactor6,
    getOverflow6,
    setOverflow6,
    getCount6,
    setCount6,
    setPeriod6,
    setMode6,
    getCompare6,
    setCompare6,
    attachInterrupt6,
    detachInterrupt6,
    refresh6,
    c_dev6,
};
#endif /*STM32_TIMER_MASK & (1 << 6)*/

#if STM32_TIMER_MASK & (1 << 7)
extern "C" {
    static inline void pause7(void)
    {
        pause(7);
    }
    static inline void resume7(void)
    {
        resume(7);
    }
    static inline uint32 getPrescaleFactor7(void)
    {
        return getPrescaleFactor(7);
    }
    static inline void setPrescaleFactor7(uint32 factor)
    {
        setPrescaleFactor(7, factor);
    }
    static inline uint16 getOverflow7(void)
    {
        return getOverflow(7);
    }
    static inline void setOverflow7(uint16 val)
    {
        setOverflow(7, val);
    }
    static inline uint16 getCount7(void)
    {
        return getCount(7);
    }
    static inline void setCount7(uint16 val)
    {
        setCount(7, val);
    }
    static inline uint16 setPeriod7(uint32 microseconds)
    {
        return setPeriod(7, microseconds);
    }
    static inline void setMode7(int channel, timer_mode mode)
    {
        setMode(7, channel, mode);
    }
    static inline uint16 getCompare7(int channel)
    {
        return getCompare(7, channel);
    }
    static inline void setCompare7(int channel, uint16 compare)
    {
        setCompare(7, channel, compare);
    }
    static inline void attachInterrupt7(int channel, voidFuncPtr handler)
    {
        attachInterrupt(7, channel, handler);
    }
    static inline void detachInterrupt7(int channel)
    {
        detachInterrupt(7, channel);
    }
    static inline void refresh7(void)
    {
        refresh(7);
    }
    static inline timer_dev* c_dev7(void)
    {
        return c_dev(7);
    }
}

struct HardwareTimer_t Timer7 = {
    pause7,
    resume7,
    getPrescaleFactor7,
    setPrescaleFactor7,
    getOverflow7,
    setOverflow7,
    getCount7,
    setCount7,
    setPeriod7,
    setMode7,
    getCompare7,
    setCompare7,
    attachInterrupt7,
    detachInterrupt7,
    refresh7,
    c_dev7,
};
#endif /*STM32_TIMER_MASK & (1 << 7)*/

#if STM32_TIMER_MASK & (1 << 8)
extern "C" {
    static inline void pause8(void)
    {
        pause(8);
    }
    static inline void resume8(void)
    {
        resume(8);
    }
    static inline uint32 getPrescaleFactor8(void)
    {
        return getPrescaleFactor(8);
    }
    static inline void setPrescaleFactor8(uint32 factor)
    {
        setPrescaleFactor(8, factor);
    }
    static inline uint16 getOverflow8(void)
    {
        return getOverflow(8);
    }
    static inline void setOverflow8(uint16 val)
    {
        setOverflow(8, val);
    }
    static inline uint16 getCount8(void)
    {
        return getCount(8);
    }
    static inline void setCount8(uint16 val)
    {
        setCount(8, val);
    }
    static inline uint16 setPeriod8(uint32 microseconds)
    {
        return setPeriod(8, microseconds);
    }
    static inline void setMode8(int channel, timer_mode mode)
    {
        setMode(8, channel, mode);
    }
    static inline uint16 getCompare8(int channel)
    {
        return getCompare(8, channel);
    }
    static inline void setCompare8(int channel, uint16 compare)
    {
        setCompare(8, channel, compare);
    }
    static inline void attachInterrupt8(int channel, voidFuncPtr handler)
    {
        attachInterrupt(8, channel, handler);
    }
    static inline void detachInterrupt8(int channel)
    {
        detachInterrupt(8, channel);
    }
    static inline void refresh8(void)
    {
        refresh(8);
    }
    static inline timer_dev* c_dev8(void)
    {
        return c_dev(8);
    }
}

struct HardwareTimer_t Timer8 = {
    pause8,
    resume8,
    getPrescaleFactor8,
    setPrescaleFactor8,
    getOverflow8,
    setOverflow8,
    getCount8,
    setCount8,
    setPeriod8,
    setMode8,
    getCompare8,
    setCompare8,
    attachInterrupt8,
    detachInterrupt8,
    refresh8,
    c_dev8,
};
#endif /*STM32_TIMER_MASK & (1 << 8)*/
#endif /*(STM32_MCU_SERIES == STM32_SERIES_F1) && defined(STM32_HIGH_DENSITY)*/
