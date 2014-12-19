
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

#include "test.h"



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

/*
void printf_usart_putc( void* p, char c) {
	usart_putc(c);
}
*/

int main_testUtils(void) {
	//PIO_Configure(pPinsNandFlash, PIO_LISTSIZE(pPinsNandFlash));
	//PIO_Configure(pPinsNf, PIO_LISTSIZE(pPinsNf));
	
	//init_printf(NULL, printf_usart_putc);
	
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
	
	testResult = 0;
	usart_puts("----- press 'c' Key to continue !!!\n\r");
	while( 'c' != usart_getc() ) {
		testResult = 0;
		mdelay(200);
	}
	
	return testResult;
}

