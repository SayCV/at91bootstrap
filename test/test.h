#ifndef __TEST_UTILS_H
#define __TEST_UTILS_H

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

#include "div.h"

#include "printf.h"

typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef uint8_t uint;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef uint8_t uchar;
typedef uint16_t ushort;
typedef uint32_t ulong;

typedef uint8_t u_char;

typedef uint32_t u_int32_t;

/*
 * Set the data bus width.
 */
typedef unsigned long datum;

typedef uint32_t size_t;
typedef int64_t loff_t;

#define __BIG_ENDIAN 1

#define cpu_writeb(value, addr) writeb(value, addr)
#define cpu_writew(value, addr) writew(value, addr)
#define cpu_writel(value, addr) writel(value, addr)
#define cpu_readb(addr) readb(addr)
#define cpu_readw(addr) readw(addr)
#define cpu_readl(addr) readl(addr)

#define BOARD_NORFLASH_ADDR 0x10000000

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

void testDDR2();
void testNAND();
void testNOR();
	
void testYC();
void testYKYX();

void dev_info(char *dev, char *p_fmt, ...);

void mdelay(unsigned int msec);

#endif /* __TEST_UTILS_H */

