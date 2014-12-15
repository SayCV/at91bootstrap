
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

/*
 * Fast Accurate Memory Test Suite
 * http://www.barrgroup.com/Embedded-Systems/How-To/Memory-Test-Suite-C
 */

#include "memtest.h"

#include "test.h"

#define BOARD_DDR2_ADDR 0x20000000
#define BOARD_DDR2_BYTES 128*1024*1024

void testDDR2(void) {
	uint32_t base_addr = BOARD_DDR2_ADDR;
	datum result = 0;
	datum pResult = NULL;
	
	usart_puts("-- Applet -- Utils Test -- DDR2 -> Start\n\r");
	
	//BOARD_ConfigureSdram();
	//BOARD_ConfigureDdram();
	
	base_addr = BOARD_DDR2_ADDR;
	result = memTestDataBus(base_addr);
	if(result == 0) {
		usart_puts("----- DDR2 TestDataBus("), 
			usart_puts(base_addr), 
			usart_puts(") succeeds\n\r");
	} else {
		usart_puts("----- DDR2 TestDataBus("), 
			usart_puts(base_addr), 
			usart_puts(") failed at first pattern("), 
			usart_puts(result), 
			usart_puts(")\n\r");
	}
	
	base_addr = BOARD_DDR2_ADDR + BOARD_DDR2_BYTES;
	result = memTestDataBus(base_addr);
	if(result == 0) {
		usart_puts("----- DDR2 TestDataBus() succeeds\n\r");
	} else {
		usart_puts("----- DDR2 TestDataBus() failed at first pattern("),
			usart_puts(result),
			usart_puts(")\n\r");
	}
	
	base_addr = BOARD_DDR2_ADDR;
	pResult = memTestAddressBus(base_addr, BOARD_DDR2_BYTES);
	if(pResult == NULL) {
		usart_puts("----- DDR2 TestAddressBus() succeeds\n\r");
	} else {
		usart_puts("----- DDR2 TestAddressBus() failed at first pattern("),
			usart_puts(pResult);
			usart_puts(")\n\r");
	}
	
	base_addr = BOARD_DDR2_ADDR;
	pResult = memTestDevice(base_addr, BOARD_DDR2_BYTES);
	if(pResult == NULL) {
		usart_puts("----- DDR2 memTestDevice() succeeds\n\r");
	} else {
		usart_puts("----- DDR2 TestDataBus() failed at first pattern("),
			usart_puts(pResult);
			usart_puts(")\n\r");
	}
	
	//地址线测试
  //'0'滑动;
  //'1'滑动;
  //"全0变全1";
  //"全1变全0";
  //"粘连测试";
  //可选"全0全1连续高速变化";
  
  //数据线测试
  //'0'滑动;
  //'1'滑动;
  //"全0变全1";
  //"全1变全0";
  //可选"全0全1连续高速变化"
  
  usart_puts("-- Applet -- Utils Test -- DDR2 -> Done\n\r");
}