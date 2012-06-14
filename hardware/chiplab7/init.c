#include "init.h"
#include "board.h"
#include <drivers/gpio/gpio.h>

void board_init(void)
{
	gpio_configure_pin(LED0_GPIO, GPIO_DIR_OUTPUT | GPIO_INIT_HIGH);
	gpio_configure_pin(LED1_GPIO, GPIO_DIR_OUTPUT | GPIO_INIT_HIGH);

	gpio_configure_pin(GPIO_JOYSTICK_PUSH,  GPIO_DIR_INPUT);
	gpio_configure_pin(GPIO_JOYSTICK_LEFT,  GPIO_DIR_INPUT);
	gpio_configure_pin(GPIO_JOYSTICK_RIGHT, GPIO_DIR_INPUT);
	gpio_configure_pin(GPIO_JOYSTICK_UP,    GPIO_DIR_INPUT);
	gpio_configure_pin(GPIO_JOYSTICK_DOWN,  GPIO_DIR_INPUT);

#if defined (CONF_BOARD_AT45DBX)
	static const gpio_map_t AT45DBX_SPI_GPIO_MAP = {
		{AT45DBX_SPI_SCK_PIN,  AT45DBX_SPI_SCK_FUNCTION},
		{AT45DBX_SPI_MISO_PIN, AT45DBX_SPI_MISO_FUNCTION},
		{AT45DBX_SPI_MOSI_PIN, AT45DBX_SPI_MOSI_FUNCTION},
#  define AT45DBX_ENABLE_NPCS_PIN(npcs, unused) \
		{AT45DBX_SPI_NPCS##npcs##_PIN, AT45DBX_SPI_NPCS##npcs##_FUNCTION},
		MREPEAT(AT45DBX_MEM_CNT, AT45DBX_ENABLE_NPCS_PIN, ~)
#  undef AT45DBX_ENABLE_NPCS_PIN
	};

	// Assign I/Os to SPI.
	gpio_enable_module(AT45DBX_SPI_GPIO_MAP,
			sizeof(AT45DBX_SPI_GPIO_MAP) / sizeof(AT45DBX_SPI_GPIO_MAP[0]));
#endif

#if defined (CONF_BOARD_SD_MMC_SPI)
	static const gpio_map_t SD_MMC_SPI_GPIO_MAP = {
		{SD_MMC_SPI_SCK_PIN,  SD_MMC_SPI_SCK_FUNCTION },
		{SD_MMC_SPI_MISO_PIN, SD_MMC_SPI_MISO_FUNCTION},
		{SD_MMC_SPI_MOSI_PIN, SD_MMC_SPI_MOSI_FUNCTION},
		{SD_MMC_SPI_NPCS_PIN, SD_MMC_SPI_NPCS_FUNCTION},
	};

	// Assign I/Os to SPI.
	gpio_enable_module(SD_MMC_SPI_GPIO_MAP,
			sizeof(SD_MMC_SPI_GPIO_MAP) / sizeof(SD_MMC_SPI_GPIO_MAP[0]));
#endif

#if defined (CONF_BOARD_TWI)
	static const gpio_map_t TWI_GPIO_MAP = {
		{AVR32_TWI_SDA_0_0_PIN, AVR32_TWI_SDA_0_0_FUNCTION},
		{AVR32_TWI_SCL_0_0_PIN, AVR32_TWI_SCL_0_0_FUNCTION},
	};

	// TWI gpio pins configuration
	gpio_enable_module(TWI_GPIO_MAP,
			sizeof(TWI_GPIO_MAP) / sizeof(TWI_GPIO_MAP[0]));
#endif

#if defined (CONF_BOARD_COM_PORT)
	// USART GPIO pin configuration.
	static const gpio_map_t COMPORT_GPIO_MAP = {
		{USART_RXD_PIN, USART_RXD_FUNCTION },
		{USART_TXD_PIN, USART_TXD_FUNCTION },
	};
	gpio_enable_module(COMPORT_GPIO_MAP,
			sizeof(COMPORT_GPIO_MAP) / sizeof(COMPORT_GPIO_MAP[0]));
#endif

#if UC3D
	static const gpio_map_t USB_GPIO_MAP = {
		{AVR32_USBC_DP_PIN, AVR32_USBC_DP_FUNCTION},
		{AVR32_USBC_DM_PIN, AVR32_USBC_DM_FUNCTION},
		{AVR32_USBC_VBUS_PIN, AVR32_USBC_VBUS_FUNCTION},
	};

	// Assign GPIO pins to USB.
	gpio_enable_module(USB_GPIO_MAP,
			sizeof(USB_GPIO_MAP) / sizeof(USB_GPIO_MAP[0]));
#endif
}
