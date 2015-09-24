#ifndef _WIRISHC_HARDWARESPI_H_
#define _WIRISHC_HARDWARESPI_H_

#include <libmaple/spi.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines the possible SPI communication speeds.
 */
typedef enum SPIFrequency {
    SPI_18MHZ       = 0, /**< 18 MHz */
    SPI_9MHZ        = 1, /**< 9 MHz */
    SPI_4_5MHZ      = 2, /**< 4.5 MHz */
    SPI_2_25MHZ     = 3, /**< 2.25 MHz */
    SPI_1_125MHZ    = 4, /**< 1.125 MHz */
    SPI_562_500KHZ  = 5, /**< 562.500 KHz */
    SPI_281_250KHZ  = 6, /**< 281.250 KHz */
    SPI_140_625KHZ  = 7, /**< 140.625 KHz */
} SPIFrequency;

#ifndef MAX_SPI_FREQS
#define MAX_SPI_FREQS 8
#endif

struct HardwareSPI_t {
    void (*begin_freq_order_mode)(SPIFrequency frequency, uint32 bitOrder, uint32 mode);
    void (*begin)(void);
    void (*beginSlave_order_mode)(uint32 bitOrder, uint32 mode);
    void (*beginSlave)(void);
    void (*end)(void);
    uint8 (*read)(void);
    void (*read_buf_len)(uint8* buffer, uint32 length);
    void (*write)(uint8 data);
    void (*write_buf_len)(const uint8* buffer, uint32 length);
    uint8 (*transfer)(uint8 data);
    uint8 (*misoPin)(void);
    uint8 (*mosiPin)(void);
    uint8 (*sckPin)(void);
    uint8 (*nssPin)(void);
    spi_dev* (*c_dev)(void);
};

#if BOARD_HAVE_SPI1
extern struct HardwareSPI_t spi1;
#endif
#if BOARD_HAVE_SPI2
extern struct HardwareSPI_t spi2;
#endif
#ifdef STM32_HIGH_DENSITY
#if BOARD_HAVE_SPI3
extern struct HardwareSPI_t spi3;
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
