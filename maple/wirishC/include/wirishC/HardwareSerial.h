#ifndef _WIRISHC_HARDWARESERIAL_H_
#define _WIRISHC_HARDWARESERIAL_H_

#include <wirish/boards.h>

#ifdef __cplusplus
extern "C" {
#endif

struct usart_dev;

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

#if BOARD_HAVE_USART1
extern struct HardwareSerial_t Serial1;
#endif
#if BOARD_HAVE_USART2
extern struct HardwareSerial_t Serial2;
#endif
#if BOARD_HAVE_USART3
extern struct HardwareSerial_t Serial3;
#endif
#if BOARD_HAVE_UART4
extern struct HardwareSerial_t Serial4;
#endif
#if BOARD_HAVE_UART5
extern struct HardwareSerial_t Serial5;
#endif
#if BOARD_HAVE_USART6
extern struct HardwareSerial_t Serial6;
#endif

#ifdef __cplusplus
}
#endif

#endif
