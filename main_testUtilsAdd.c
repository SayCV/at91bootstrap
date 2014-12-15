
#include "common.h"
#include "hardware.h"
#include "arch/at91_ccfg.h"
#include "arch/at91_rstc.h"
#include "arch/at91_pmc.h"
#include "arch/at91_smc.h"
#include "arch/at91_pio.h"
#include "arch/at91_ddrsdrc.h"
#include "gpio.h"
#include "pmc.h"
#include "usart.h"
#include "debug.h"
#include "ddramc.h"
#include "slowclk.h"
#include "timer.h"
#include "watchdog.h"
#include "string.h"
#include "at91sam9x5ek.h"

#include "onewire_info.h"

#include "usart.h"

#include "test/test.h"

#define VENDOR_DTU_CPU_V1 0
#define VENDOR_DTU_SP_V1  1
#define VENDOR_NDTU_FA_V1 10
#define BOARD_VENDOR VENDOR_NDTU_FA_V1

#define DEBUG_NCS0   0 /* Nor Flash */
#define DEBUG_NCS1   1 /* DDR2 */
#define DEBUG_NCS2   2 /* Ext. */
#define DEBUG_NCS3   3 /* Ext. */
#define DEBUG_NCS4   4 /* Ext. */
#define DEBUG_NCS5   5 /* Ext. */

#define DEBUG_YKYX 1

#define DEBUG_DDR2 1
#define DEBUG_NAND 1
#define DEBUG_NOR  1

#define DEBUG_YC   1
#define DEBUG_YKYX 1

static int testResult = 0;

/*
#if defined(DEBUG_DDR2) && DEBUG_DDR2
#include "test/test-DDR2.c"
#endif

#if defined(DEBUG_NAND) && DEBUG_NAND
#include "test/test-NAND.c"
#endif

#if defined(DEBUG_NOR) && DEBUG_NOR
#include "test/test-NOR.c"
#endif

#if defined(DEBUG_YC) && DEBUG_YC
#include "test/test-YC.c"
#endif

#if defined(DEBUG_YKYX) && DEBUG_YKYX
#include "test/test-YKYX.c"
#endif
*/

int testUtils(void) {
	//PIO_Configure(pPinsNandFlash, PIO_LISTSIZE(pPinsNandFlash));
	//PIO_Configure(pPinsNf, PIO_LISTSIZE(pPinsNf));
	
	usart_puts("---------------------------------\n\r");
	usart_puts("---------------------------------\n\r");
	usart_puts("-- Applet -- Utils Test Start\n\r");
	usart_puts("---------------------------------\n\r");
	usart_puts("---------------------------------\n\r");
	
	testDDR2();
	testNAND();
	testNOR();
	
	testYC();
	testYKYX();
	
	usart_puts("---------------------------------\n\r");
	usart_puts("---------------------------------\n\r");
	usart_puts("-- Applet -- Utils Test Done\n\r");
	usart_puts("---------------------------------\n\r");
	usart_puts("---------------------------------\n\r");
	
	return testResult;
}

void nandflash_hw_enable(void) {
	unsigned int reg;
	
	reg = readl(AT91C_BASE_CCFG + CCFG_EBICSA);
	reg |= AT91C_EBI_CS3A_SM;
	if (get_cm_rev() == 'A')
		reg &= ~AT91C_EBI_NFD0_ON_D16;
	else
		reg |= (AT91C_EBI_DDR_MP_EN | AT91C_EBI_NFD0_ON_D16);

	reg &= ~AT91C_EBI_DRV;
	writel(reg, AT91C_BASE_CCFG + CCFG_EBICSA);
}

void nandflash_hw_disable(void)
{
	unsigned int reg;
	
	reg = readl(AT91C_BASE_CCFG + CCFG_EBICSA);
	reg |=  AT91C_EBI_CS3A_SM;		/* Chip Select 3 Assignment */
		
	reg &= ~AT91C_EBI_NFD0_ON_D16;							/* NAND Flash Data Bus Selection: D0 */
	reg &= ~AT91C_EBI_DDR_MP_EN;										/* DDR Multi-port Enable (default) */
		
	reg &= ~AT91C_EBI_DRV;							/* Data Bus Pull-up Configuration: ON */
																			/* Data Bus Pull-down Configuration: OFF */
	
	writel(reg, AT91C_BASE_CCFG + CCFG_EBICSA);
}

#define SMC_MODE_DBW_Pos 12
#define SMC_MODE_DBW_Msk (0x3u << SMC_MODE_DBW_Pos) /**< \brief (SMC_MODE) Data Bus Width */
#define SMC_MODE_DBW(value) ((SMC_MODE_DBW_Msk & ((value) << SMC_MODE_DBW_Pos)))
void at91_smc_init(int cs, int width)
{
/* Configure SMC CS0 */
	writel((AT91C_SMC_NWESETUP_(1)
		| AT91C_SMC_NCS_WRSETUP_(0)
		| AT91C_SMC_NRDSETUP_(2)
		| AT91C_SMC_NCS_RDSETUP_(0)),
		AT91C_BASE_SMC + SMC_SETUP0 + 0x10*cs);

	writel((AT91C_SMC_NWEPULSE_(14)
		| AT91C_SMC_NCS_WRPULSE_(14)
		| AT91C_SMC_NRDPULSE_(14)
		| AT91C_SMC_NCS_RDPULSE_(14)),
		AT91C_BASE_SMC + SMC_PULSE0 + 0x10*cs);

	writel((AT91C_SMC_NWECYCLE_(25)
		| AT91C_SMC_NRDCYCLE_(25)),
		AT91C_BASE_SMC + SMC_CYCLE0 + 0x10*cs);

	writel((AT91C_SMC_READMODE
		| AT91C_SMC_WRITEMODE
		| AT91C_SMC_NWAITM_NWAIT_DISABLE
		| SMC_MODE_DBW(div(width, 16))
		| AT91_SMC_TDF_(5)),
		AT91C_BASE_SMC + SMC_CTRL0 + 0x10*cs);
}

#if 0
void norflash_smc_init(int width)
{
/* Configure SMC CS0 */
	writel((AT91C_SMC_NWESETUP_(1)
		| AT91C_SMC_NCS_WRSETUP_(0)
		| AT91C_SMC_NRDSETUP_(2)
		| AT91C_SMC_NCS_RDSETUP_(0)),
		AT91C_BASE_SMC + SMC_SETUP3);

	writel((AT91C_SMC_NWEPULSE_(14)
		| AT91C_SMC_NCS_WRPULSE_(14)
		| AT91C_SMC_NRDPULSE_(14)
		| AT91C_SMC_NCS_RDPULSE_(14)),
		AT91C_BASE_SMC + SMC_PULSE3);

	writel((AT91C_SMC_NWECYCLE_(25)
		| AT91C_SMC_NRDCYCLE_(25)),
		AT91C_BASE_SMC + SMC_CYCLE3);

	writel((AT91C_SMC_READMODE
		| AT91C_SMC_WRITEMODE
		| AT91C_SMC_NWAITM_NWAIT_DISABLE
		| SMC_MODE_DBW(div(width, 16))
		| AT91_SMC_TDF_(5)),
		AT91C_BASE_SMC + SMC_CTRL3);
}
#endif

void norflash_hw_init(void)
{
	unsigned int reg;

	/* Configure NorFlash PINs */
	const struct pio_desc nor_pins[] = {
		/*{"NANDOE",	AT91C_PIN_PD(0),		0, PIO_PULLUP, PIO_PERIPH_A},
		{"NANDWE",	AT91C_PIN_PD(1),		0, PIO_PULLUP, PIO_PERIPH_A},
		{"NANDALE",	AT91C_PIN_PD(2),	0, PIO_PULLUP, PIO_PERIPH_A},
		{"NANDCLE",	AT91C_PIN_PD(3),	0, PIO_PULLUP, PIO_PERIPH_A},
		{"NANDCS",	AT91C_PIN_PD(4),	1, PIO_PULLUP, PIO_OUTPUT},
		{"NANDWAIT",	AT91C_PIN_PD(5),	0, PIO_PULLUP, PIO_INPUT},
		{"D0",	AT91C_PIN_PD(6), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"D1",	AT91C_PIN_PD(7), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"D2",	AT91C_PIN_PD(8), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"D3",	AT91C_PIN_PD(9), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"D4",	AT91C_PIN_PD(10), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"D5",	AT91C_PIN_PD(11), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"D6",	AT91C_PIN_PD(12), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"D7",	AT91C_PIN_PD(13), 0, PIO_PULLUP, PIO_PERIPH_A},*/
		{"A20",	AT91C_PIN_PD(15), 0, PIO_PULLUP, PIO_PERIPH_B},
		{"A21",	AT91C_PIN_PD(16), 0, PIO_PULLUP, PIO_PERIPH_B},
		{"A22",	AT91C_PIN_PD(17), 0, PIO_PULLUP, PIO_PERIPH_B},
		{"A23",	AT91C_PIN_PD(18), 0, PIO_PULLUP, PIO_PERIPH_B},
		{"NCS2",	AT91C_PIN_PD(19), 0, PIO_PULLUP, PIO_PERIPH_B},
		{"NCS3",	AT91C_PIN_PD(20), 0, PIO_PULLUP, PIO_PERIPH_B},
		{"NCS4",	AT91C_PIN_PD(21), 0, PIO_PULLUP, PIO_PERIPH_B},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	nandflash_hw_disable();
	
	at91_smc_init(DEBUG_NCS0, 16);

	/* Configure the PIO controller */
	pio_configure(nor_pins);

	pmc_enable_periph_clock(AT91C_ID_PIOC_D);
}
