#include "SSD1306.hpp"
#include "board.h"
#include "conf_clock.h"

SSD1306Framebuffer::SSD1306Framebuffer(volatile avr32_spi_t* spi_, unsigned char spi_chip_, uint32_t pin_dc_, uint32_t pin_rst_, FBDimensionType width_, FBDimensionType height_, uint8_t* data_) :
    Framebuffer(width_, height_, data_),
    num_pages(height / 8), // 8 pixel rows per data byte
    num_columns(width),
    pin_dc(pin_dc_),
    pin_rst(pin_rst_),
    spi_chip(spi_chip_),
    spi(spi_)
{
}

inline void SSD1306Framebuffer::modeCmd()
{
    gpio_clr_gpio_pin(pin_dc);
}

inline void SSD1306Framebuffer::modeData()
{
    gpio_set_gpio_pin(pin_dc);
}

void SSD1306Framebuffer::writeData(uint8_t val)
{
    while ((AVR32_SPI.sr & AVR32_SPI_SR_TDRE_MASK) == 0);
    //~ modeData();
    AVR32_SPI.tdr = (val << AVR32_SPI_TDR_TD_OFFSET);
    //~ while ((AVR32_SPI.sr & AVR32_SPI_SR_TDRE_MASK) == 0);
}

void SSD1306Framebuffer::writeCmd(uint8_t val)
{
    spi_selectChip(spi, spi_chip);
    while ((AVR32_SPI.sr & AVR32_SPI_SR_TDRE_MASK) == 0);
    modeCmd();
    AVR32_SPI.tdr = (val << AVR32_SPI_TDR_TD_OFFSET);
    //~ while ((AVR32_SPI.sr & AVR32_SPI_SR_TDRE_MASK) == 0);
    spi_unselectChip(spi, spi_chip);
}

void SSD1306Framebuffer::resetHigh()
{
    gpio_set_gpio_pin(pin_rst);
}

void SSD1306Framebuffer::resetLow()
{
    gpio_clr_gpio_pin(pin_rst);
}

void SSD1306Framebuffer::delay(uint32_t val)
{
    /// \bug busy wait uncalibrated
    while(--val){
        for(int j = 0; j < 20; ++j)
        {
            asm volatile ("nop\n");
        }
    }
}

/// \note GPIO pins must be assigned to SPI module using gpio_enable_module() before initializing the display.
void SSD1306Framebuffer::initSPI()
{
    // SPI OLED options.
    spi_options_t spiOptions;
    spiOptions.reg          = spi_chip;
    #if FPBA_HZ < 10000000
    spiOptions.baudrate     = FPBA_HZ;
    #else
    spiOptions.baudrate     = 10000000; // SSD1306 datasheet says min 100ns clock cycle
    #endif
    spiOptions.bits         = 8;
    spiOptions.spck_delay   = 0;
    spiOptions.trans_delay  = 0;
    spiOptions.stay_act     = 1;
    spiOptions.spi_mode     = 0;
    spiOptions.modfdis      = 1;

    // If the SPI used by the SD/MMC is not enabled.
    if (!spi_is_enabled(spi))
    {
        // Initialize as master.
        spi_initMaster(spi, &spiOptions);

        // Set selection mode: variable_ps, pcs_decode, delay.
        spi_selectionMode(spi, 0, 0, 0);

        // Enable SPI.
        spi_enable(spi);
    }

    // Setup SPI registers according to spiOptions.
    spi_setupChipReg(spi, &spiOptions, FPBA_HZ);
}

void SSD1306Framebuffer::setPage(uint8_t page)
{
    writeCmd(cmd_setPage);
    writeCmd(page);  // start
    writeCmd(num_pages - 1);     // after page 7 we wrap around
}

void SSD1306Framebuffer::setColumn(uint8_t col)
{
    writeCmd(cmd_setColumn);
    writeCmd(col);  // start
    writeCmd(num_columns - 1);  // after column 127 we move to the next page
}

void SSD1306Framebuffer::init()
{
    if (data == 0)
    {
        data = static_cast<uint8_t*>(malloc(kSize));
    }
    initSPI();
    resetLow();
    delay(30);
    resetHigh();
    delay(30);
    // Charge Pump Setting
    writeCmd(0x8d);
    writeCmd(0x14);
    writeCmd(0xaf);
    // Set Display Clock
    writeCmd(0xD5);
    writeCmd(0xF0);
    // Set Pre-charge Period
    writeCmd(0xD9);
    writeCmd(0x11);
    // Set VCOMH Deselect Level
    writeCmd(0xDb);
    writeCmd(0x0);
    // Set Norma Display
    writeCmd(0xa6);
    // Entire Display ON
    //~ writeCmd(0xa5);
    // Set Contrast Control
    writeCmd(0x81);
    writeCmd(0xff);  //1-256
    // Set Segment Re-map
    writeCmd(0xa1);
    // Set COM Output Scan Direction
    writeCmd(0xc8);
    // Set Memory Addressing Mode = horizontal
    writeCmd(0x20);
    writeCmd(0x00);
    // Set Fade Out and Blinking
    //~ writeCmd(0x23);
    //~ writeCmd(0x30);

}

void SSD1306Framebuffer::flush()
{
    // Data is split into pages, one page is 64 x 8 bits
    // Each byte represents 8 rows and 1 column on the display

    // We will write 8 lines at a time.
    uint8_t* data_ptr;
    //~ setPage(offset_y);
    setPage(0);
    setColumn(0);
    modeData();
    spi_selectChip(spi, spi_chip);
    //~ data_ptr = data + offset_y * num_columns;
    //~ for (uint8_t page = offset_y; page < num_pages; ++page)
    //~ {
        //~ // setPage(page); // not necessary because of memory horizontal addressing mode, see datasheet for SSD1306.
        //~ for (uint8_t column = 0; column < num_columns; ++column)
        //~ {
            //~ writeData(*data_ptr);
            //~ spi_write(spi, *data_ptr);
            //~ ++data_ptr;
            //~ delay(10); // for debugging
        //~ }
    //~ }
    data_ptr = data;
    //~ for (uint8_t page = 0; page < offset_y; ++page)
    for (uint8_t page = 0; page < num_pages; ++page)
    {
        // setPage(page); // not necessary because of memory horizontal addressing mode, see datasheet for SSD1306.
        for (uint8_t column = 0; column < num_columns; ++column)
        {
            //~ writeData(*data_ptr);
            spi_write(spi, *data_ptr);
            ++data_ptr;
            //~ delay(10); // for debugging
        }
    }
    spi_unselectChip(spi, spi_chip);
}

void SSD1306Framebuffer::vscroll8(int8_t offset)
{
    offset_y += offset;
    offset_y %= num_pages;
}
