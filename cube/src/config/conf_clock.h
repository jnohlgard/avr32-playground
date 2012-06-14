#ifndef CONF_CLOCK_H_INCLUDED
#define CONF_CLOCK_H_INCLUDED

/**
 * @name System Clock Frequencies
 * @{
 */
#define FCPU_HZ     (60000000)
#define FPBA_HZ     (60000000)
#define FPBB_HZ     (60000000)
#define FHSB_HZ     (60000000)
#define FPLL0_HZ    (120000000)
#define FPLL1_HZ    (48000000)
//! @}

#define F_CPU       (FCPU_HZ)


//#define CONFIG_SYSCLK_INIT_CPUMASK  (1 << SYSCLK_SYSTIMER)
//#define CONFIG_SYSCLK_INIT_PBAMASK  (1 << SYSCLK_USART0)
//#define CONFIG_SYSCLK_INIT_PBBMASK  (1 << SYSCLK_HMATRIX)
//#define CONFIG_SYSCLK_INIT_HSBMASK  (1 << SYSCLK_MDMA_HSB)
// Disable all non-essential peripheral clocks
#define CONFIG_SYSCLK_INIT_CPUMASK  0
#define CONFIG_SYSCLK_INIT_PBAMASK  0
#define CONFIG_SYSCLK_INIT_PBBMASK  0
#define CONFIG_SYSCLK_INIT_HSBMASK  0

//#define CONFIG_SYSCLK_SOURCE        SYSCLK_SRC_RCSYS
//#define CONFIG_SYSCLK_SOURCE        SYSCLK_SRC_OSC0
#define CONFIG_SYSCLK_SOURCE          SYSCLK_SRC_PLL0

/* Fbus = Fsys / (2 ^ BUS_div) */
#define CONFIG_SYSCLK_CPU_DIV         1
#define CONFIG_SYSCLK_PBA_DIV         1
#define CONFIG_SYSCLK_PBB_DIV         1

//#define CONFIG_USBCLK_SOURCE        USBCLK_SRC_OSC0
//#define CONFIG_USBCLK_SOURCE        USBCLK_SRC_PLL0
#define CONFIG_USBCLK_SOURCE          USBCLK_SRC_PLL1

/* Fusb = Fsys / USB_div */
#define CONFIG_USBCLK_DIV             1 /* Fusb = Fsys/(2 ^ USB_div) */

#define CONFIG_PLL0_SOURCE            PLL_SRC_OSC0
//#define CONFIG_PLL0_SOURCE          PLL_SRC_OSC1

/* Fpll0 = (Fclk * PLL_mul) / PLL_div */
#define CONFIG_PLL0_MUL               (FPLL0_HZ / BOARD_OSC0_HZ)
#define CONFIG_PLL0_DIV               1

#define   CONFIG_PLL1_SOURCE          PLL_SRC_OSC0
//#define CONFIG_PLL1_SOURCE          PLL_SRC_OSC1

/* Fpll1 = (Fclk * PLL_mul) / PLL_div */
#define CONFIG_PLL1_MUL               (FPLL1_HZ / BOARD_OSC0_HZ)
#define CONFIG_PLL1_DIV               1

#endif /* CONF_CLOCK_H_INCLUDED */
