#ifndef FRAMEBUFFER_SSD1306_HPP_
#define FRAMEBUFFER_SSD1306_HPP_

#include "Framebuffer.hpp"
extern "C"
{
    #include <avr32/io.h>
    // ASF includes
    #include <drivers/gpio/gpio.h>
    #include <drivers/spi/spi.h>
}

class SSD1306Framebuffer : public Framebuffer
{
    private:
        const uint32_t num_pages;
        const uint32_t num_columns;
        const uint32_t pin_dc;
        const uint32_t pin_rst;
        const unsigned char spi_chip;
        volatile avr32_spi_t* spi;

        void modeCmd();
        void modeData();
        void writeCmd(uint8_t val);
        void writeData(uint8_t val);
        void resetHigh();
        void resetLow();
        void delay(uint32_t val);
        void initSPI();

        /// Set page (y * 8)
        void setPage(uint8_t page);

        /// Set column (x)
        void setColumn(uint8_t col);

    public:
        explicit SSD1306Framebuffer(volatile avr32_spi_t* spi_, unsigned char spi_chip_, uint32_t pin_dc_, uint32_t pin_rst_, FBDimensionType width_, FBDimensionType height_, uint8_t* data_ = 0);

        void init();
        void flush();
        void vscroll8(int8_t offset);


    private:
        // Hardware commands, see datasheet
        static const uint8_t cmd_setColumn = 0x21;
        static const uint8_t cmd_setPage   = 0x22;
};
#endif
