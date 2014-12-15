
#include "common.h"
#include "hardware.h"
#include "board.h"
#include "usart.h"
#include "debug.h"
#include "slowclk.h"
#include "dataflash.h"
#include "nandflash.h"
#include "sdcard.h"
#include "flash.h"
#include "string.h"
#include "onewire_info.h"

#define VENDOR_DTU_CPU_V1 0
#define VENDOR_DTU_SP_V1  1
#define VENDOR_NDTU_FA_V1 10
#define BOARD_VENDOR VENDOR_NDTU_FA_V1

#define DEBUG_DDR2 1
#define DEBUG_NAND 1
#define DEBUG_NOR  1

#define DEBUG_YC   1
#define DEBUG_YKYX 1

static int testResult = 0;

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