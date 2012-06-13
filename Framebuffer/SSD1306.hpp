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
        static const uint32_t pin_sda  = AVR32_PIN_PA14;
        static const uint32_t pin_scl  = AVR32_PIN_PA15;
        static const uint32_t pin_dc   = AVR32_PIN_PA21;
        static const uint32_t pin_rst  = AVR32_PIN_PA22;
        static const uint32_t pin_cs   = AVR32_PIN_PA16;
        static const uint32_t spi_port = 0;

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
        SSD1306Framebuffer(FBDimensionType width_, FBDimensionType height_);

        void init();
        void flush();
};
#endif
