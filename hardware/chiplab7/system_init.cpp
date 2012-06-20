#include "system_init.h"
#include "board.h"
#include "conf_system.h"

#include "system/framebuffer.hpp"
#include "Framebuffer/SSD1306.hpp"
#include <services/clock/sysclk.h>

#ifdef CONF_SYSTEM_OLED
extern "C"
{
void initOLEDFramebuffer()
{
    sysclk_enable_peripheral_clock(SSD1306_SPI);
    static SSD1306Framebuffer oled(SSD1306_SPI, SSD1306_SPI_NPCS, SSD1306_GPIO_DC_PIN, SSD1306_GPIO_RST_PIN, SSD1306_DISPLAY_WIDTH, SSD1306_DISPLAY_HEIGHT);
    fb = &oled;
    fb->init();
    fb->clear();
    fb->flush();
}
}
#endif

