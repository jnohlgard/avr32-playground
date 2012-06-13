#include "SSD1306.hpp"

SSD1306Framebuffer::SSD1306Framebuffer(FBDimensionType width_, FBDimensionType height_) :
    Framebuffer(width_, height_),
    num_pages(height / 8), // 8 pixel rows per data byte
    num_columns(width)
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
    modeData();
    spi_selectChip(&AVR32_SPI, spi_port);
    while ((AVR32_SPI.sr & AVR32_SPI_SR_TDRE_MASK) == 0);
    AVR32_SPI.tdr = (val << AVR32_SPI_TDR_TD_OFFSET);
    while ((AVR32_SPI.sr & AVR32_SPI_SR_TDRE_MASK) == 0);
    spi_unselectChip(&AVR32_SPI, spi_port);
}

void SSD1306Framebuffer::writeCmd(uint8_t val)
{
    modeCmd();
    spi_selectChip(&AVR32_SPI, spi_port);
    while ((AVR32_SPI.sr & AVR32_SPI_SR_TDRE_MASK) == 0);
    AVR32_SPI.tdr = (val << AVR32_SPI_TDR_TD_OFFSET);
    //~ while ((AVR32_SPI.sr & AVR32_SPI_SR_TDRE_MASK) == 0);
    spi_unselectChip(&AVR32_SPI, spi_port);
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

void SSD1306Framebuffer::initSPI()
{
    // GPIO pins used for OLED interface
    static const gpio_map_t SPI_GPIO_MAP =
    {
        {AVR32_SPI_SCK_0_0_PIN,  AVR32_SPI_SCK_0_0_FUNCTION },  // SPI Clock.
        {AVR32_SPI_MISO_0_0_PIN, AVR32_SPI_MISO_0_0_FUNCTION},  // MISO.
        {AVR32_SPI_MOSI_0_0_PIN, AVR32_SPI_MOSI_0_0_FUNCTION},  // MOSI.
        {AVR32_SPI_NPCS_0_0_PIN, AVR32_SPI_NPCS_0_0_FUNCTION}  // Chip Select NPCS0.
    };

    // SPI OLED options.
    spi_options_t spiOptions;
    spiOptions.reg          = 0;
    spiOptions.baudrate     = 30000000;
    spiOptions.bits         = 8;
    spiOptions.spck_delay   = 0;
    spiOptions.trans_delay  = 0;
    spiOptions.stay_act     = 1;
    spiOptions.spi_mode     = 0;
    spiOptions.modfdis      = 1;

    // Assign I/Os to SPI.
    gpio_enable_module(SPI_GPIO_MAP,
                       sizeof(SPI_GPIO_MAP) / sizeof(SPI_GPIO_MAP[0]));

    // If the SPI used by the SD/MMC is not enabled.
    if (!spi_is_enabled(&AVR32_SPI))
    {
        // Initialize as master.
        spi_initMaster(&AVR32_SPI, &spiOptions);

        // Set selection mode: variable_ps, pcs_decode, delay.
        spi_selectionMode(&AVR32_SPI, 0, 0, 0);

        // Enable SPI.
        spi_enable(&AVR32_SPI);
    }

    // Setup SPI registers according to spiOptions.
    spi_setupChipReg(&AVR32_SPI, &spiOptions, 30000000);

}

void SSD1306Framebuffer::setPage(uint8_t page)
{
    writeCmd(0x22);
    writeCmd(page);  // start
    writeCmd(7);     // after this page we wrap around
}

void SSD1306Framebuffer::setColumn(uint8_t col)
{
    writeCmd(0x21);
    writeCmd(col);  // start
    writeCmd(127);  // after this column we move to the next page
}

void SSD1306Framebuffer::init()
{
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
    uint8_t* data_ptr = &data[0];
    setPage(0);
    setColumn(0);
    for (uint8_t page = 0; page < num_pages; ++page)
    {
        // setPage(page); // not necessary because of memory horizontal addressing mode, see datasheet for SSD1306.
        for (uint8_t column = 0; column < num_columns; ++column)
        {
            writeData(*data_ptr);
            ++data_ptr;
            //~ delay(10); // for debugging
        }
    }
}
