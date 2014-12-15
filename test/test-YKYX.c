
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

uint32_t commandAddress, command;
uint32_t YKYX_BASE = 0x60000000;

void testYKYX(void) {
	
	usart_puts("-- Applet -- Utils Test -- YKYX -> Start\n\r");
	
	usart_puts("-- Read All YXs --\n\r");
	usart_puts("EXNCS1_YX1 - "), 
		usart_putint(YKYX_BASE + 0), 
		usart_putint(*(volatile uint16_t *)(YKYX_BASE + 0)), 
		usart_puts("\n");
	usart_puts("EXNCS2_YX2 - "), 
		usart_putint(YKYX_BASE + 2), 
		usart_putint(*(volatile uint16_t *)(YKYX_BASE + 2)), 
		usart_puts("\n");
	usart_puts("EXNCS3_YX3 - "), 
		usart_putint(YKYX_BASE + 4), 
		usart_putint(*(volatile uint16_t *)(YKYX_BASE + 4)), 
		usart_puts("\n");
	usart_puts("-- Read All YXs -- Done\n\r");
	
	usart_puts("-- Make All YKs to Validate --\n\r");
	*(volatile uint16_t *)(YKYX_BASE + 6) = (uint16_t)0xA50A;
	*(volatile uint16_t *)(YKYX_BASE + 8) = (uint16_t)0xFFFF;
	*(volatile uint16_t *)(YKYX_BASE + 10) = (uint16_t)0xFFFF;
	usart_puts("EXNCS4_YK_PWD_KEY - "), 
		usart_putint(YKYX_BASE + 6), 
		usart_putint(0xA525), 
		usart_puts("\n");
	usart_puts("EXNCS5_YK1 - "), 
		usart_putint(YKYX_BASE + 8), 
		usart_putint(0xFFFF), 
		usart_puts("\n");
	usart_puts("EXNCS6_YK2 - "), 
		usart_putint(YKYX_BASE + 10), 
		usart_putint(0xFFFF), 
		usart_puts("\n");
	
	usart_puts("-- Read All YKYXs --\n\r");
	usart_puts("EXNCS7_YKYX1 - "), 
		usart_putint(YKYX_BASE + 12), 
		usart_putint(*(volatile uint16_t *)(YKYX_BASE + 12)), 
		usart_puts("\n");
	usart_puts("EXNCS8_YKYX2 - "), 
		usart_putint(YKYX_BASE + 14), 
		usart_putint(*(volatile uint16_t *)(YKYX_BASE + 14)), 
		usart_puts("\n");
	usart_puts("-- Read All YKYXs -- Done --\n\r");
	
	usart_puts("-- Applet -- Utils Test -- YKYX -> Done\n\r");
}