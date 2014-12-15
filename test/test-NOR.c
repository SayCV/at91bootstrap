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

#define BOARD_NORFLASH_ADDR 0x10000000

void testNOR(void) {       
	uint32_t base_addr = BOARD_NORFLASH_ADDR;
	
	uint32_t manuf_id=0;
	uint32_t manuf_id_ext1=0;
	uint32_t manuf_id_ext2=0;
	uint32_t manuf_id_ext3=0;
	uint32_t manuf_id_ext4=0;
	
	uint32_t query_id1=0;
	uint32_t query_id2=0;
	uint32_t query_id3=0;
	
	//nandflash_hw_disable();
	norflash_hw_init();
	//at91_smc_init(DEBUG_NCS0, 16);
	
	/* Here is an example of Autoselect mode (getting manufacturer ID) */
	/* Auto Select Entry */
	*( (uint16_t *)base_addr + 0x555 ) = 0x00AA; /* write unlock cycle 1 */
	*( (uint16_t *)base_addr + 0x2AA ) = 0x0055; /* write unlock cycle 2 */
	*( (uint16_t *)base_addr + 0x555 ) = 0x0090; /* write autoselect command */
	/* multiple reads can be performed after entry */
	manuf_id = *( (uint32_t *)base_addr + 0x000 ); /* read manuf. id */
	manuf_id_ext1 = *( (uint32_t *)base_addr + 0x001 );
	manuf_id_ext2 = *( (uint32_t *)base_addr + 0x00E );
	manuf_id_ext3 = *( (uint32_t *)base_addr + 0x00F );
	manuf_id_ext4 = *( (uint32_t *)base_addr + 0x001 );
	/* Autoselect exit */
	*( (uint16_t *)base_addr + 0x000 ) = 0x00F0; /* exit autoselect (write reset command) */
	
	/* Example: CFI Entry command */
	*( (uint16_t *)base_addr + 0x55 ) = 0x0098; /* write CFI entry command */
	query_id1 = *( (uint32_t *)base_addr + 0x010 );
	query_id2 = *( (uint32_t *)base_addr + 0x011 );
	query_id3 = *( (uint32_t *)base_addr + 0x012 );
	/* Example: CFI Exit command */
	*( (uint16_t *)base_addr + 0x000 ) = 0x00F0; /* write cfi exit command */
	
	usart_puts("-- Applet -- Utils Test -- NOR -> Start\n\r");
	
	usart_puts("----- manuf_id  = "), usart_putint(manuf_id), usart_puts("\n");
	usart_puts("----- manuf_id1 = "), usart_putint(manuf_id_ext1), usart_puts("\n");
	usart_puts("----- manuf_id2 = "), usart_putint(manuf_id_ext2), usart_puts("\n");
	usart_puts("----- manuf_id3 = "), usart_putint(manuf_id_ext3), usart_puts("\n");
	usart_puts("----- manuf_id4 = "), usart_putint(manuf_id_ext4), usart_puts("\n");
	
	usart_puts("----- query_id1 = "), usart_putint(query_id1), usart_puts("\n");
	usart_puts("----- query_id2 = "), usart_putint(query_id2), usart_puts("\n");
	usart_puts("----- query_id3 = "), usart_putint(query_id3), usart_puts("\n");
	
	usart_puts("-- Applet -- Utils Test -- NOR -> Done\n\r");
}

