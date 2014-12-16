
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

#include "test.h"

uint32_t commandAddress, command;
uint32_t YKYX_BASE = 0x60000000;

void testYKYX(void) {
	
	nandflash_hw_disable();
	//norflash_hw_init();
	at91_smc_init(DEBUG_NCS5, 16);
	
	usart_puts("-- Applet -- Utils Test -- YKYX -> Start\n\r");
	
	usart_puts("-- Read All YXs --\n\r");
	dbg_info("----- EXNCS1_YX1(%d) = %d\n", YKYX_BASE + 0, *(volatile uint16_t *)(YKYX_BASE + 0));
	dbg_info("----- EXNCS2_YX2(%d) = %d\n", YKYX_BASE + 2, *(volatile uint16_t *)(YKYX_BASE + 2));
	dbg_info("----- EXNCS3_YX3(%d) = %d\n", YKYX_BASE + 4, *(volatile uint16_t *)(YKYX_BASE + 4));
	usart_puts("-- Read All YXs -- Done\n\r");
	
	usart_puts("-- Make All YKs to Validate --\n\r");
	*(volatile uint16_t *)(YKYX_BASE + 6) = (uint16_t)0xA50A;
	*(volatile uint16_t *)(YKYX_BASE + 8) = (uint16_t)0xFFFF;
	*(volatile uint16_t *)(YKYX_BASE + 10) = (uint16_t)0xFFFF;
	dbg_info("----- EXNCS4_YK_PWD_KEY(%d) = %d\n", YKYX_BASE + 6, 0xA525);
	dbg_info("----- EXNCS5_YK1(%d) = %d\n", YKYX_BASE + 8, 0xFFFF);
	dbg_info("----- EXNCS6_YK2(%d) = %d\n", YKYX_BASE + 10, 0xFFFF);
	
	usart_puts("-- Read All YKYXs --\n\r");
	dbg_info("----- EXNCS7_YKYX1(%d) = %d\n", YKYX_BASE + 12, *(volatile uint16_t *)(YKYX_BASE + 12));
	dbg_info("----- EXNCS8_YKYX2(%d) = %d\n", YKYX_BASE + 14, *(volatile uint16_t *)(YKYX_BASE + 14));
	usart_puts("-- Read All YKYXs -- Done --\n\r");
	
	usart_puts("-- Applet -- Utils Test -- YKYX -> Done\n\r");
}