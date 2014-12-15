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


void testDDR2();
void testNAND();
void testNOR();
	
void testYC();
void testYKYX();
	
#endif /* __TEST_UTILS_H */

