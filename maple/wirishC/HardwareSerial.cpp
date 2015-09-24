#include <wirish/HardwareSerial.h>
struct HardwareSerial_t {
    void (*begin)(uint32 baud);
    void (*end)(void);
    uint32 (*available)(void);
    uint8 (*read)(void);
    void (*flush)(void);
    void (*write)(unsigned char);
    int (*txPin)(void);
    int (*rxPin)(void);
    struct usart_dev* (*c_dev)(void);
};

extern "C" {
    static void begin(uint32 SerialPortNumber, uint32 baud)
    {
        switch (SerialPortNumber) {
#if BOARD_HAVE_USART1
            case 1:
                SERIAL1.begin(baud);
                break;
#endif
#if BOARD_HAVE_USART2
            case 2:
                SERIAL2.begin(baud);
                break;
#endif
#if BOARD_HAVE_USART3
            case 3:
                SERIAL3.begin(baud);
                break;
#endif
#if BOARD_HAVE_USART4
            case 4:
                SERIAL4.begin(baud);
                break;
#endif
#if BOARD_HAVE_USART5
            case 5:
                SERIAL5.begin(baud);
                break;
#endif
#if BOARD_HAVE_USART6
            case 6:
                SERIAL6.begin(baud);
                break;
#endif
            default:
                ASSERT(0);
        }
    }

    static void end(uint32 SerialPortNumber)
    {
        switch (SerialPortNumber) {
#if BOARD_HAVE_USART1
            case 1:
                SERIAL1.end();
                break;
#endif
#if BOARD_HAVE_USART2
            case 2:
                SERIAL2.end();
                break;
#endif
#if BOARD_HAVE_USART3
            case 3:
                SERIAL3.end();
                break;
#endif
#if BOARD_HAVE_USART4
            case 4:
                SERIAL4.end();
                break;
#endif
#if BOARD_HAVE_USART5
            case 5:
                SERIAL5.end();
                break;
#endif
#if BOARD_HAVE_USART6
            case 6:
                SERIAL6.end();
                break;
#endif
            default:
                ASSERT(0);
        }
    }

    static uint32 available(uint32 SerialPortNumber)
    {
        switch (SerialPortNumber) {
#if BOARD_HAVE_USART1
            case 1:
                return SERIAL1.available();
#endif
#if BOARD_HAVE_USART2
            case 2:
                return SERIAL2.available();
#endif
#if BOARD_HAVE_USART3
            case 3:
                return SERIAL3.available();
#endif
#if BOARD_HAVE_USART4
            case 4:
                return SERIAL4.available();
#endif
#if BOARD_HAVE_USART5
            case 5:
                return SERIAL5.available();
#endif
#if BOARD_HAVE_USART6
            case 6:
                return SERIAL6.available();
#endif
            default:
                ASSERT(0);
        }
        return 0;
    }

    static uint8 read(uint32 SerialPortNumber)
    {
        switch (SerialPortNumber) {
#if BOARD_HAVE_USART1
            case 1:
                return SERIAL1.read();
#endif
#if BOARD_HAVE_USART2
            case 2:
                return SERIAL2.read();
#endif
#if BOARD_HAVE_USART3
            case 3:
                return SERIAL3.read();
#endif
#if BOARD_HAVE_USART4
            case 4:
                return SERIAL4.read();
#endif
#if BOARD_HAVE_USART5
            case 5:
                return SERIAL5.read();
#endif
#if BOARD_HAVE_USART6
            case 6:
                return SERIAL6.read();
#endif
            default:
                ASSERT(0);
        }
        return 0;
    }

    static void flush(uint32 SerialPortNumber)
    {
        switch (SerialPortNumber) {
#if BOARD_HAVE_USART1
            case 1:
                SERIAL1.flush();
                break;
#endif
#if BOARD_HAVE_USART2
            case 2:
                SERIAL2.flush();
                break;
#endif
#if BOARD_HAVE_USART3
            case 3:
                SERIAL3.flush();
                break;
#endif
#if BOARD_HAVE_USART4
            case 4:
                SERIAL4.flush();
                break;
#endif
#if BOARD_HAVE_USART5
            case 5:
                SERIAL5.flush();
                break;
#endif
#if BOARD_HAVE_USART6
            case 6:
                SERIAL6.flush();
                break;
#endif
            default:
                ASSERT(0);
        }
    }

    static void write(uint32 SerialPortNumber, unsigned char ch)
    {
        switch (SerialPortNumber) {
#if BOARD_HAVE_USART1
            case 1:
                SERIAL1.write(ch);
                break;
#endif
#if BOARD_HAVE_USART2
            case 2:
                SERIAL2.write(ch);
                break;
#endif
#if BOARD_HAVE_USART3
            case 3:
                SERIAL3.write(ch);
                break;
#endif
#if BOARD_HAVE_USART4
            case 4:
                SERIAL4.write(ch);
                break;
#endif
#if BOARD_HAVE_USART5
            case 5:
                SERIAL5.write(ch);
                break;
#endif
#if BOARD_HAVE_USART6
            case 6:
                SERIAL6.write(ch);
                break;
#endif
            default:
                ASSERT(0);
        }
    }

    static int txPin(uint32 SerialPortNumber)
    {
        switch (SerialPortNumber) {
#if BOARD_HAVE_USART1
            case 1:
                return SERIAL1.txPin();
#endif
#if BOARD_HAVE_USART2
            case 2:
                return SERIAL2.txPin();
#endif
#if BOARD_HAVE_USART3
            case 3:
                return SERIAL3.txPin();
#endif
#if BOARD_HAVE_USART4
            case 4:
                return SERIAL4.txPin();
#endif
#if BOARD_HAVE_USART5
            case 5:
                return SERIAL5.txPin();
#endif
#if BOARD_HAVE_USART6
            case 6:
                return SERIAL6.txPin();
#endif
            default:
                ASSERT(0);
        }
        return 0;
    }

    static int rxPin(uint32 SerialPortNumber)
    {
        switch (SerialPortNumber) {
#if BOARD_HAVE_USART1
            case 1:
                return SERIAL1.rxPin();
#endif
#if BOARD_HAVE_USART2
            case 2:
                return SERIAL2.rxPin();
#endif
#if BOARD_HAVE_USART3
            case 3:
                return SERIAL3.rxPin();
#endif
#if BOARD_HAVE_USART4
            case 4:
                return SERIAL4.rxPin();
#endif
#if BOARD_HAVE_USART5
            case 5:
                return SERIAL5.rxPin();
#endif
#if BOARD_HAVE_USART6
            case 6:
                return SERIAL6.rxPin();
#endif
            default:
                ASSERT(0);
        }
        return 0;
    }

    static struct usart_dev* c_dev(uint32 SerialPortNumber)
    {
        switch (SerialPortNumber) {
#if BOARD_HAVE_USART1
            case 1:
                return SERIAL1.c_dev();
#endif
#if BOARD_HAVE_USART2
            case 2:
                return SERIAL2.c_dev();
#endif
#if BOARD_HAVE_USART3
            case 3:
                return SERIAL3.c_dev();
#endif
#if BOARD_HAVE_USART4
            case 4:
                return SERIAL4.c_dev();
#endif
#if BOARD_HAVE_USART5
            case 5:
                return SERIAL5.c_dev();
#endif
#if BOARD_HAVE_USART6
            case 6:
                return SERIAL6.c_dev();
#endif
            default:
                ASSERT(0);
        }
        return 0;
    }
}

#if BOARD_HAVE_USART1
extern "C" {
    static inline void begin1(uint32 baud)
    {
        begin(1, baud);
    }
    static inline void end1(void)
    {
        end(1);
    }
    static inline uint32 available1(void)
    {
        return available(1);
    }
    static inline uint8 read1(void)
    {
        return read(1);
    }
    static inline void flush1(void)
    {
        flush(1);
    }
    static inline void write1(unsigned char ch)
    {
        write(1, ch);
    }
    static inline int txPin1(void)
    {
        return txPin(1);
    }
    static inline int rxPin1(void)
    {
        return rxPin(1);
    }
    static inline struct usart_dev* c_dev1(void)
    {
        return c_dev(1);
    }
}

struct HardwareSerial_t Serial1 = {
    begin1,
    end1,
    available1,
    read1,
    flush1,
    write1,
    txPin1,
    rxPin1,
    c_dev1,
};
#endif /*BOARD_HAVE_USART1*/

#if BOARD_HAVE_USART2
extern "C" {
    static inline void begin2(uint32 baud)
    {
        begin(2, baud);
    }
    static inline void end2(void)
    {
        end(2);
    }
    static inline uint32 available2(void)
    {
        return available(2);
    }
    static inline uint8 read2(void)
    {
        return read(2);
    }
    static inline void flush2(void)
    {
        flush(2);
    }
    static inline void write2(unsigned char ch)
    {
        write(2, ch);
    }
    static inline int txPin2(void)
    {
        return txPin(2);
    }
    static inline int rxPin2(void)
    {
        return rxPin(2);
    }
    static inline struct usart_dev* c_dev2(void)
    {
        return c_dev(2);
    }
}

struct HardwareSerial_t Serial2 = {
    begin2,
    end2,
    available2,
    read2,
    flush2,
    write2,
    txPin2,
    rxPin2,
    c_dev2,
};
#endif /*BOARD_HAVE_USART2*/

#if BOARD_HAVE_USART3
extern "C" {
    static inline void begin3(uint32 baud)
    {
        begin(3, baud);
    }
    static inline void end3(void)
    {
        end(3);
    }
    static inline uint32 available3(void)
    {
        return available(3);
    }
    static inline uint8 read3(void)
    {
        return read(3);
    }
    static inline void flush3(void)
    {
        flush(3);
    }
    static inline void write3(unsigned char ch)
    {
        write(3, ch);
    }
    static inline int txPin3(void)
    {
        return txPin(3);
    }
    static inline int rxPin3(void)
    {
        return rxPin(3);
    }
    static inline struct usart_dev* c_dev3(void)
    {
        return c_dev(3);
    }
}

struct HardwareSerial_t Serial3 = {
    begin3,
    end3,
    available3,
    read3,
    flush3,
    write3,
    txPin3,
    rxPin3,
    c_dev3,
};
#endif /*BOARD_HAVE_USART3*/

#if BOARD_HAVE_USART4
extern "C" {
    static inline void begin4(uint32 baud)
    {
        begin(4, baud);
    }
    static inline void end4(void)
    {
        end(4);
    }
    static inline uint32 available4(void)
    {
        return available(4);
    }
    static inline uint8 read4(void)
    {
        return read(4);
    }
    static inline void flush4(void)
    {
        flush(4);
    }
    static inline void write4(unsigned char ch)
    {
        write(4, ch);
    }
    static inline int txPin4(void)
    {
        return txPin(4);
    }
    static inline int rxPin4(void)
    {
        return rxPin(4);
    }
    static inline struct usart_dev* c_dev4(void)
    {
        return c_dev(4);
    }
}

struct HardwareSerial_t Serial4 = {
    begin4,
    end4,
    available4,
    read4,
    flush4,
    write4,
    txPin4,
    rxPin4,
    c_dev4,
};
#endif /*BOARD_HAVE_USART4*/

#if BOARD_HAVE_USART5
extern "C" {
    static inline void begin5(uint32 baud)
    {
        begin(5, baud);
    }
    static inline void end5(void)
    {
        end(5);
    }
    static inline uint32 available5(void)
    {
        return available(5);
    }
    static inline uint8 read5(void)
    {
        return read(5);
    }
    static inline void flush5(void)
    {
        flush(5);
    }
    static inline void write5(unsigned char ch)
    {
        write(5, ch);
    }
    static inline int txPin5(void)
    {
        return txPin(5);
    }
    static inline int rxPin5(void)
    {
        return rxPin(5);
    }
    static inline struct usart_dev* c_dev5(void)
    {
        return c_dev(5);
    }
}

struct HardwareSerial_t Serial5 = {
    begin5,
    end5,
    available5,
    read5,
    flush5,
    write5,
    txPin5,
    rxPin5,
    c_dev5,
};
#endif /*BOARD_HAVE_USART5*/

#if BOARD_HAVE_USART6
extern "C" {
    static inline void begin6(uint32 baud)
    {
        begin(6, baud);
    }
    static inline void end6(void)
    {
        end(6);
    }
    static inline uint32 available6(void)
    {
        return available(6);
    }
    static inline uint8 read6(void)
    {
        return read(6);
    }
    static inline void flush6(void)
    {
        flush(6);
    }
    static inline void write6(unsigned char ch)
    {
        write(6, ch);
    }
    static inline int txPin6(void)
    {
        return txPin(6);
    }
    static inline int rxPin6(void)
    {
        return rxPin(6);
    }
    static inline struct usart_dev* c_dev6(void)
    {
        return c_dev(6);
    }
}

struct HardwareSerial_t Serial6 = {
    begin6,
    end6,
    available6,
    read6,
    flush6,
    write6,
    txPin6,
    rxPin6,
    c_dev6,
};
#endif /*BOARD_HAVE_USART6*/
