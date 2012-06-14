/**
 * \file
 *
 * \brief User board definition template
 *
 */

#ifndef USER_BOARD_H
#define USER_BOARD_H

/* This file is intended to contain definitions and configuration details for
 * features and devices that are available on the board, e.g., frequency and
 * startup time for an external crystal, external memory devices, LED and USART
 * pins.
 */
#include "compiler.h"

#define FOSC32          32768                                 //!< Osc32 frequency: Hz.
#define OSC32_STARTUP   AVR32_PM_OSCCTRL32_STARTUP_8192_RCOSC //!< Osc32 startup time: RCOsc periods.

#define FOSC0           12000000                              //!< Osc0 frequency: Hz.
#define OSC0_STARTUP    AVR32_PM_OSCCTRL0_STARTUP_2048_RCOSC  //!< Osc0 startup time: RCOsc periods.

/* These are documented in services/basic/clock/uc3b0_b1/osc.h */
#define BOARD_OSC0_HZ           12000000
#define BOARD_OSC0_STARTUP_US   17000
#define BOARD_OSC0_IS_XTAL      true
#define BOARD_OSC32_HZ          32768
#define BOARD_OSC32_STARTUP_US  71000
#define BOARD_OSC32_IS_XTAL     true

//! Number of LEDs.
#define LED_COUNT   2

/*! \name GPIO Connections of LEDs
 */
//! @{
#define LED0_GPIO   AVR32_PIN_PA07
#define LED1_GPIO   AVR32_PIN_PA08
//! @}

/*! \name GPIO Connections of the Joystick
 */
//! @{
#define GPIO_JOYSTICK_PUSH            AVR32_PIN_PA13
#define GPIO_JOYSTICK_PUSH_PRESSED    0
#define GPIO_JOYSTICK_LEFT            AVR32_PIN_PB04
#define GPIO_JOYSTICK_LEFT_PRESSED    0
#define GPIO_JOYSTICK_RIGHT           AVR32_PIN_PB03
#define GPIO_JOYSTICK_RIGHT_PRESSED   0
#define GPIO_JOYSTICK_UP              AVR32_PIN_PB02
#define GPIO_JOYSTICK_UP_PRESSED      0
#define GPIO_JOYSTICK_DOWN            AVR32_PIN_PB05
#define GPIO_JOYSTICK_DOWN_PRESSED    0
//! @}

/*! \name ADC Connection of the Voltage Divider
 */
//! @{
#define ADC_RW1_CHANNEL     7
#define ADC_RW1_PIN         AVR32_ADC_AD_7_PIN
#define ADC_RW1_FUNCTION    AVR32_ADC_AD_7_FUNCTION
//! @}

/*! \name ADC Connection of the Light Sensor
 */
//! @{
#define ADC_LIGHT_CHANNEL           6
#define ADC_LIGHT_PIN               AVR32_ADC_AD_6_PIN
#define ADC_LIGHT_FUNCTION          AVR32_ADC_AD_6_FUNCTION
//! @}

/*! \name GPIO and SPI Connections of the SD/MMC Connector
 */
//! @{
#define SD_MMC_CARD_DETECT_PIN      AVR32_PIN_PB00
#define SD_MMC_WRITE_PROTECT_PIN    AVR32_PIN_PB01
#define SD_MMC_SPI                  (&AVR32_SPI)
#define SD_MMC_SPI_NPCS             1
#define SD_MMC_SPI_SCK_PIN          AVR32_SPI_SCK_0_0_PIN
#define SD_MMC_SPI_SCK_FUNCTION     AVR32_SPI_SCK_0_0_FUNCTION
#define SD_MMC_SPI_MISO_PIN         AVR32_SPI_MISO_0_0_PIN
#define SD_MMC_SPI_MISO_FUNCTION    AVR32_SPI_MISO_0_0_FUNCTION
#define SD_MMC_SPI_MOSI_PIN         AVR32_SPI_MOSI_0_0_PIN
#define SD_MMC_SPI_MOSI_FUNCTION    AVR32_SPI_MOSI_0_0_FUNCTION
#define SD_MMC_SPI_NPCS_PIN         AVR32_SPI_NPCS_1_0_PIN
#define SD_MMC_SPI_NPCS_FUNCTION    AVR32_SPI_NPCS_1_0_FUNCTION
//! @}

/*! \name SPI Connections of the SSD1306 OLED display controller
 */
//! @{
#define SSD1306_SPI                 (&AVR32_SPI)
#define SSD1306_SPI_NPCS            0
#define SSD1306_SPI_SCK_PIN         AVR32_SPI_SCK_0_0_PIN
#define SSD1306_SPI_SCK_FUNCTION    AVR32_SPI_SCK_0_0_FUNCTION
#define SSD1306_SPI_MISO_PIN        AVR32_SPI_MISO_0_0_PIN
#define SSD1306_SPI_MISO_FUNCTION   AVR32_SPI_MISO_0_0_FUNCTION
#define SSD1306_SPI_MOSI_PIN        AVR32_SPI_MOSI_0_0_PIN
#define SSD1306_SPI_MOSI_FUNCTION   AVR32_SPI_MOSI_0_0_FUNCTION
#define SSD1306_SPI_NPCS0_PIN       AVR32_SPI_NPCS_0_0_PIN
#define SSD1306_SPI_NPCS0_FUNCTION  AVR32_SPI_NPCS_0_0_FUNCTION
//! @}

/*! \name USART connection to the UC3B board controller
 */
//! @{
#define USART                       (&AVR32_USART1)
#define USART_RXD_PIN               AVR32_USART1_RXD_0_0_PIN
#define USART_RXD_FUNCTION          AVR32_USART1_RXD_0_0_FUNCTION
#define USART_TXD_PIN               AVR32_USART1_TXD_0_0_PIN
#define USART_TXD_FUNCTION          AVR32_USART1_TXD_0_0_FUNCTION
#define USART_IRQ                   AVR32_USART1_IRQ
#define USART_IRQ_GROUP             AVR32_USART1_IRQ_GROUP
#define USART_SYSCLK                SYSCLK_USART1
//! @}

/*! \name SSC and TWI connections of the WM8978 audio codec
 */
//! @{
// The SSC is used for streaming data to the codec
#define WM8978_SSC                   (&AVR32_SSC)
#define WM8978_SSC_RX_SYNC_PIN       AVR32_SSC_RX_FRAME_SYNC_0_PIN
#define WM8978_SSC_RX_SYNC_FUNCTION  AVR32_SSC_RX_FRAME_SYNC_0_FUNCTION
#define WM8978_SSC_TX_SYNC_PIN       AVR32_SSC_TX_FRAME_SYNC_0_PIN
#define WM8978_SSC_TX_SYNC_FUNCTION  AVR32_SSC_TX_FRAME_SYNC_0_FUNCTION
#define WM8978_SSC_RX_DATA_PIN       AVR32_SSC_RX_DATA_0_PIN
#define WM8978_SSC_RX_DATA_FUNCTION  AVR32_SSC_RX_DATA_0_FUNCTION
#define WM8978_SSC_RX_CLOCK_PIN      AVR32_SSC_RX_CLOCK_0_PIN
#define WM8978_SSC_RX_CLOCK_FUNCTION AVR32_SSC_RX_CLOCK_0_FUNCTION
#define WM8978_SSC_TX_DATA_PIN       AVR32_SSC_TX_DATA_0_PIN
#define WM8978_SSC_TX_DATA_FUNCTION  AVR32_SSC_TX_DATA_0_FUNCTION
#define WM8978_SSC_TX_CLOCK_PIN      AVR32_SSC_TX_CLOCK_0_PIN
#define WM8978_SSC_TX_CLOCK_FUNCTION AVR32_SSC_TX_CLOCK_0_FUNCTION
// The TWI is used for setting registers on the codec
#define WM8978_TWI                   (&AVR32_TWI)
#define WM8978_TWI_SCL_PIN           AVR32_TWI_SCL_0_0_PIN
#define WM8978_TWI_SCL_FUNCTION      AVR32_TWI_SCL_0_0_FUNCTION
#define WM8978_TWI_SDA_PIN           AVR32_TWI_SDA_0_0_PIN
#define WM8978_TWI_SDA_FUNCTION      AVR32_TWI_SDA_0_0_FUNCTION
//! @}

/*! \name TWI Connections of the Spare TWI Connector
 */
//! @{
#define SPARE_TWI                   (&AVR32_TWI)
#define SPARE_TWI_SCL_PIN           AVR32_TWI_SCL_0_0_PIN
#define SPARE_TWI_SCL_FUNCTION      AVR32_TWI_SCL_0_0_FUNCTION
#define SPARE_TWI_SDA_PIN           AVR32_TWI_SDA_0_0_PIN
#define SPARE_TWI_SDA_FUNCTION      AVR32_TWI_SDA_0_0_FUNCTION
//! @}

#endif // USER_BOARD_H
