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

const char *dev = "NOR: ";

/* Configure NorFlash PINs */
	const struct pio_desc test_nor_pins[] = {
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

void testNOR(void) {
	uint32_t i = 0;
	   
	uint32_t base_addr = BOARD_NORFLASH_ADDR;
	
	uint32_t manuf_id=0;
	uint32_t manuf_id_ext1=0;
	uint32_t manuf_id_ext2=0;
	uint32_t manuf_id_ext3=0;
	uint32_t manuf_id_ext4=0;
	
	uint32_t query_id1=0;
	uint32_t query_id2=0;
	uint32_t query_id3=0;
/*	
	usart_puts("-- Applet -- Utils Test -- NOR PINs -> Start\n\r");
	nandflash_hw_disable();
	//norflash_hw_init();
	//Configure the PIO controller
	pio_configure(test_nor_pins);
	usart_puts("----- NOR PINs: PD15-21 -- Output HIGH, press 'c' Key to continue !!!\n\r");
	usart_puts("----- That's point at PCBA: \n\r");
	usart_puts("----- | PD15 | PD16 | PD17 | PD18 | PD19 | PD20 | PD21 |\n\r");
	usart_puts("----- | PD15 | PD16 | PD17 | PD18 | PD19 | PD20 | PD21 |\n\r");
	while( 'c' != usart_getc() ) {
		mdelay(200);
	}
	usart_puts("----- NOR PINs: PD15-21 -- Output LOW, press 'c' Key to continue !!!\n\r");
	while( 'c' != usart_getc() ) {
		mdelay(200);
	}
	usart_puts("-- Applet -- Utils Test -- NOR PINs -> Results provided by User's Meter\n\r");
	usart_puts("-- Applet -- Utils Test -- NOR PINs -> Can not detect EBI PINs: NCS0, NRE,NRD\n\r");
	usart_puts("-- Applet -- Utils Test -- NOR PINs -> END\n\r");
*/	
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
	
	//usart_puts("----- manuf_id  = "), usart_putint(manuf_id), usart_puts("\n");
	dbg_info("----- manuf_id  = %d\n", manuf_id);
	dbg_info("----- manuf_id_ext1  = %d\n", manuf_id_ext1);
	dbg_info("----- manuf_id_ext1  = %d\n", manuf_id_ext2);
	dbg_info("----- manuf_id_ext1  = %d\n", manuf_id_ext3);
	dbg_info("----- manuf_id_ext1  = %d\n", manuf_id_ext4);
	
	dbg_info("----- query_id1  = %d\n", query_id1);
	dbg_info("----- query_id2  = %d\n", query_id2);
	dbg_info("----- query_id3  = %d\n", query_id3);
	
	usart_puts("-- Applet -- Utils Test -- NOR -> Done\n\r");
}

