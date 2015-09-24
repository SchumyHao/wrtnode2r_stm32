#include <wirish/HardwareSPI.h>

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
static HardwareSPI CPP_SPI1(1);
#endif
#if BOARD_HAVE_SPI2
static HardwareSPI CPP_SPI2(2);
#endif
#ifdef STM32_HIGH_DENSITY
#if BOARD_HAVE_SPI3
static HardwareSPI CPP_SPI3(3);
#endif
#endif

extern "C" {
    static void begin_freq_order_mode(uint32 spiPortNumber, SPIFrequency frequency, uint32 bitOrder, uint32 mode)
    {
        switch (spiPortNumber) {
#if BOARD_HAVE_SPI1
            case 1:
                CPP_SPI1.begin(frequency, bitOrder, mode);
                break;
#endif
#if BOARD_HAVE_SPI2
            case 2:
                CPP_SPI2.begin(frequency, bitOrder, mode);
                break;
#endif
#ifdef STM32_HIGH_DENSITY
#if BOARD_HAVE_SPI3
            case 3:
                CPP_SPI3.begin(frequency, bitOrder, mode);
                break;
#endif
#endif
            default:
                ASSERT(0);
        }
    }

    static void begin(uint32 spiPortNumber)
    {
        switch (spiPortNumber) {
#if BOARD_HAVE_SPI1
            case 1:
                CPP_SPI1.begin();
                break;
#endif
#if BOARD_HAVE_SPI2
            case 2:
                CPP_SPI2.begin();
                break;
#endif
#ifdef STM32_HIGH_DENSITY
#if BOARD_HAVE_SPI3
            case 3:
                CPP_SPI3.begin();
                break;
#endif
#endif
            default:
                ASSERT(0);
        }
    }

    static void beginSlave_order_mode(uint32 spiPortNumber, uint32 bitOrder, uint32 mode)
    {
        switch (spiPortNumber) {
#if BOARD_HAVE_SPI1
            case 1:
                CPP_SPI1.beginSlave(bitOrder, mode);
                break;
#endif
#if BOARD_HAVE_SPI2
            case 2:
                CPP_SPI2.beginSlave(bitOrder, mode);
                break;
#endif
#ifdef STM32_HIGH_DENSITY
#if BOARD_HAVE_SPI3
            case 3:
                CPP_SPI3.beginSlave(bitOrder, mode);
                break;
#endif
#endif
            default:
                ASSERT(0);
        }
    }

    static void beginSlave(uint32 spiPortNumber)
    {
        switch (spiPortNumber) {
#if BOARD_HAVE_SPI1
            case 1:
                CPP_SPI1.beginSlave();
                break;
#endif
#if BOARD_HAVE_SPI2
            case 2:
                CPP_SPI2.beginSlave();
                break;
#endif
#ifdef STM32_HIGH_DENSITY
#if BOARD_HAVE_SPI3
            case 3:
                CPP_SPI3.beginSlave();
                break;
#endif
#endif
            default:
                ASSERT(0);
        }
    }

    static void end(uint32 spiPortNumber)
    {
        switch (spiPortNumber) {
#if BOARD_HAVE_SPI1
            case 1:
                CPP_SPI1.end();
                break;
#endif
#if BOARD_HAVE_SPI2
            case 2:
                CPP_SPI2.end();
                break;
#endif
#ifdef STM32_HIGH_DENSITY
#if BOARD_HAVE_SPI3
            case 3:
                CPP_SPI3.end();
                break;
#endif
#endif
            default:
                ASSERT(0);
        }
    }

    static uint8 read(uint32 spiPortNumber)
    {
        switch (spiPortNumber) {
#if BOARD_HAVE_SPI1
            case 1:
                return CPP_SPI1.read();
#endif
#if BOARD_HAVE_SPI2
            case 2:
                return CPP_SPI2.read();
#endif
#ifdef STM32_HIGH_DENSITY
#if BOARD_HAVE_SPI3
            case 3:
                return CPP_SPI3.read();
#endif
#endif
            default:
                ASSERT(0);
        }
        return 0;
    }

    static void read_buf_len(uint32 spiPortNumber, uint8* buffer, uint32 length)
    {
        switch (spiPortNumber) {
#if BOARD_HAVE_SPI1
            case 1:
                CPP_SPI1.read(buffer, length);
                break;
#endif
#if BOARD_HAVE_SPI2
            case 2:
                CPP_SPI2.read(buffer, length);
                break;
#endif
#ifdef STM32_HIGH_DENSITY
#if BOARD_HAVE_SPI3
            case 3:
                CPP_SPI3.read(buffer, length);
                break;
#endif
#endif
            default:
                ASSERT(0);
        }
    }

    static void write(uint32 spiPortNumber, uint8 data)
    {
        switch (spiPortNumber) {
#if BOARD_HAVE_SPI1
            case 1:
                CPP_SPI1.write(data);
                break;
#endif
#if BOARD_HAVE_SPI2
            case 2:
                CPP_SPI2.write(data);
                break;
#endif
#ifdef STM32_HIGH_DENSITY
#if BOARD_HAVE_SPI3
            case 3:
                CPP_SPI3.write(data);
                break;
#endif
#endif
            default:
                ASSERT(0);
        }
    }

    static void write_buf_len(uint32 spiPortNumber, const uint8* buffer, uint32 length)
    {
        switch (spiPortNumber) {
#if BOARD_HAVE_SPI1
            case 1:
                CPP_SPI1.write(buffer, length);
                break;
#endif
#if BOARD_HAVE_SPI2
            case 2:
                CPP_SPI2.write(buffer, length);
                break;
#endif
#ifdef STM32_HIGH_DENSITY
#if BOARD_HAVE_SPI3
            case 3:
                CPP_SPI3.write(buffer, length);
                break;
#endif
#endif
            default:
                ASSERT(0);
        }
    }

    static uint8 transfer(uint32 spiPortNumber, uint8 data)
    {
        switch (spiPortNumber) {
#if BOARD_HAVE_SPI1
            case 1:
                return CPP_SPI1.transfer(data);
#endif
#if BOARD_HAVE_SPI2
            case 2:
                return SPI2.transfer(data);
#endif
#ifdef STM32_HIGH_DENSITY
#if BOARD_HAVE_SPI3
            case 3:
                return SPI3.transfer(data);
#endif
#endif
            default:
                ASSERT(0);
        }
        return 0;
    }

    static uint8 misoPin(uint32 spiPortNumber)
    {
        switch (spiPortNumber) {
#if BOARD_HAVE_SPI1
            case 1:
                return CPP_SPI1.misoPin();
#endif
#if BOARD_HAVE_SPI2
            case 2:
                return CPP_SPI2.misoPin();
#endif
#ifdef STM32_HIGH_DENSITY
#if BOARD_HAVE_SPI3
            case 3:
                return CPP_SPI3.misoPin();
#endif
#endif
            default:
                ASSERT(0);
        }
        return 0;
    }

    static uint8 mosiPin(uint32 spiPortNumber)
    {
        switch (spiPortNumber) {
#if BOARD_HAVE_SPI1
            case 1:
                return CPP_SPI1.mosiPin();
#endif
#if BOARD_HAVE_SPI2
            case 2:
                return CPP_SPI2.mosiPin();
#endif
#ifdef STM32_HIGH_DENSITY
#if BOARD_HAVE_SPI3
            case 3:
                return CPP_SPI3.mosiPin();
#endif
#endif
            default:
                ASSERT(0);
        }
        return 0;
    }

    static uint8 sckPin(uint32 spiPortNumber)
    {
        switch (spiPortNumber) {
#if BOARD_HAVE_SPI1
            case 1:
                return CPP_SPI1.sckPin();
#endif
#if BOARD_HAVE_SPI2
            case 2:
                return CPP_SPI2.sckPin();
#endif
#ifdef STM32_HIGH_DENSITY
#if BOARD_HAVE_SPI3
            case 3:
                return CPP_SPI3.sckPin();
#endif
#endif
            default:
                ASSERT(0);
        }
        return 0;
    }

    static uint8 nssPin(uint32 spiPortNumber)
    {
        switch (spiPortNumber) {
#if BOARD_HAVE_SPI1
            case 1:
                return CPP_SPI1.nssPin();
#endif
#if BOARD_HAVE_SPI2
            case 2:
                return CPP_SPI2.nssPin();
#endif
#ifdef STM32_HIGH_DENSITY
#if BOARD_HAVE_SPI3
            case 3:
                return CPP_SPI3.nssPin();
#endif
#endif
            default:
                ASSERT(0);
        }
        return 0;
    }

    static spi_dev* c_dev(uint32 spiPortNumber)
    {
        switch (spiPortNumber) {
#if BOARD_HAVE_SPI1
            case 1:
                return CPP_SPI1.c_dev();
#endif
#if BOARD_HAVE_SPI2
            case 2:
                return CPP_SPI2.c_dev();
#endif
#ifdef STM32_HIGH_DENSITY
#if BOARD_HAVE_SPI3
            case 3:
                return CPP_SPI3.c_dev();
#endif
#endif
            default:
                ASSERT(0);
        }
        return NULL;
    }
}




#if BOARD_HAVE_SPI1
extern "C" {
    static inline void begin_freq_order_mode1(SPIFrequency frequency, uint32 bitOrder, uint32 mode)
    {
        begin_freq_order_mode(1, frequency, bitOrder, mode);
    }
    static inline void begin1(void)
    {
        begin(1);
    }
    static inline void beginSlave_order_mode1(uint32 bitOrder, uint32 mode)
    {
        beginSlave_order_mode(1, bitOrder, mode);
    }
    static inline void beginSlave1(void)
    {
        beginSlave(1);
    }
    static inline void end1(void)
    {
        end(1);
    }
    static inline uint8 read1(void)
    {
        return read(1);
    }
    static inline void read_buf_len1(uint8* buffer, uint32 length)
    {
        read_buf_len(1, buffer, length);
    }
    static inline void write1(uint8 data)
    {
        write(1, data);
    }
    static inline void write_buf_len1(const uint8* buffer, uint32 length)
    {
        write_buf_len(1, buffer, length);
    }
    static inline uint8 transfer1(uint8 data)
    {
        return transfer(1, data);
    }
    static inline uint8 misoPin1(void)
    {
        return misoPin(1);
    }
    static inline uint8 mosiPin1(void)
    {
        return mosiPin(1);
    }
    static inline uint8 sckPin1(void)
    {
        return sckPin(1);
    }
    static inline uint8 nssPin1(void)
    {
        return nssPin(1);
    }
    static inline spi_dev* c_dev1(void)
    {
        return c_dev(1);
    }
}

struct HardwareSPI_t spi1 = {
    begin_freq_order_mode1,
    begin1,
    beginSlave_order_mode1,
    beginSlave1,
    end1,
    read1,
    read_buf_len1,
    write1,
    write_buf_len1,
    transfer1,
    misoPin1,
    mosiPin1,
    sckPin1,
    nssPin1,
    c_dev1,
};
#endif /*BOARD_HAVE_SPI1*/

#if BOARD_HAVE_SPI2
extern "C" {
    static inline void begin_freq_order_mode2(SPIFrequency frequency, uint32 bitOrder, uint32 mode)
    {
        begin_freq_order_mode(2, frequency, bitOrder, mode);
    }
    static inline void begin2(void)
    {
        begin(2);
    }
    static inline void beginSlave_order_mode2(uint32 bitOrder, uint32 mode)
    {
        beginSlave_order_mode(2, bitOrder, mode);
    }
    static inline void beginSlave2(void)
    {
        beginSlave(2);
    }
    static inline void end2(void)
    {
        end(2);
    }
    static inline uint8 read2(void)
    {
        return read(2);
    }
    static inline void read_buf_len2(uint8* buffer, uint32 length)
    {
        read_buf_len(2, buffer, length);
    }
    static inline void write2(uint8 data)
    {
        write(2, data);
    }
    static inline void write_buf_len2(const uint8* buffer, uint32 length)
    {
        write_buf_len(2, buffer, length);
    }
    static inline uint8 transfer2(uint8 data)
    {
        return transfer(2, data);
    }
    static inline uint8 misoPin2(void)
    {
        return misoPin(2);
    }
    static inline uint8 mosiPin2(void)
    {
        return mosiPin(2);
    }
    static inline uint8 sckPin2(void)
    {
        return sckPin(2);
    }
    static inline uint8 nssPin2(void)
    {
        return nssPin(2);
    }
    static inline spi_dev* c_dev2(void)
    {
        return c_dev(2);
    }
}

struct HardwareSPI_t spi2 = {
    begin_freq_order_mode2,
    begin2,
    beginSlave_order_mode2,
    beginSlave2,
    end2,
    read2,
    read_buf_len2,
    write2,
    write_buf_len2,
    transfer2,
    misoPin2,
    mosiPin2,
    sckPin2,
    nssPin2,
    c_dev2,
};
#endif/*BOARD_HAVE_SPI2*/

#ifdef STM32_HIGH_DENSITY
#if BOARD_HAVE_SPI3
extern "C" {
    static inline void begin_freq_order_mode3(SPIFrequency frequency, uint32 bitOrder, uint32 mode)
    {
        begin_freq_order_mode(3, frequency, bitOrder, mode);
    }
    static inline void begin3(void)
    {
        begin(3);
    }
    static inline void beginSlave_order_mode3(uint32 bitOrder, uint32 mode)
    {
        beginSlave_order_mode(3, bitOrder, mode);
    }
    static inline void beginSlave3(void)
    {
        beginSlave(3);
    }
    static inline void end3(void)
    {
        end(3);
    }
    static inline uint8 read3(void)
    {
        return read(3);
    }
    static inline void read_buf_len3(uint8* buffer, uint32 length)
    {
        read_buf_len(3, buffer, length);
    }
    static inline void write3(uint8 data)
    {
        write(3, data);
    }
    static inline void write_buf_len3(const uint8* buffer, uint32 length)
    {
        write_buf_len(3, buffer, length);
    }
    static inline uint8 transfer3(uint8 data)
    {
        return transfer(3, data);
    }
    static inline uint8 misoPin3(void)
    {
        return misoPin(3);
    }
    static inline uint8 mosiPin3(void)
    {
        return mosiPin(3);
    }
    static inline uint8 sckPin3(void)
    {
        return sckPin(3);
    }
    static inline uint8 nssPin3(void)
    {
        return nssPin(3);
    }
    static inline spi_dev* c_dev3(void)
    {
        return c_dev(3);
    }
}

struct HardwareSPI_t spi3 = {
    begin_freq_order_mode3,
    begin3,
    beginSlave_order_mode3,
    beginSlave3,
    end3,
    read3,
    read_buf_len3,
    write3,
    write_buf_len3,
    transfer3,
    misoPin3,
    mosiPin3,
    sckPin3,
    nssPin3,
    c_dev3,
};
#endif/*BOARD_HAVE_SPI3*/
#endif/*STM32_HIGH_DENSITY*/
