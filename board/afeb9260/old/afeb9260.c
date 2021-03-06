/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support  -  ROUSSET  -
 * ----------------------------------------------------------------------------
 * Copyright (c) 2006, Atmel Corporation

 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaiimer below.
 *
 * - Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the disclaimer below in the documentation and/or
 * other materials provided with the distribution.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 * File Name           : at91sam9260ek.c
 * Object              :
 * Creation            : NLe Jul 13th 2006
 * ODi Nov 9th         : dstp #3507 "Bad PIO descriptors in at91samxxxek.c"
 *-----------------------------------------------------------------------------
 */
#include "../../include/part.h"
#include "../../include/gpio.h"
#include "../../include/pmc.h"
#include "../../include/debug.h"
#include "../../include/sdramc.h"
#include "../../include/main.h"
#ifdef CFG_NANDFLASH
#include "../../include/nandflash.h"
#endif
#ifdef CFG_DATAFLASH
#include "../../include/dataflash.h"
#endif
#ifdef CFG_FLASH
#include "../../include/flash.h"
#endif

/* We init NAND regardless of whatever */
/*------------------------------------------------------------------------------*/
/* \fn    nandflash_hw_init							*/
/* \brief NandFlash HW init							*/
/*------------------------------------------------------------------------------*/
void nandflash_hw_init(void)
{
    /*
     * Setup Smart Media, first enable the address range of CS3 in HMATRIX user interface 
     */
    writel(readl(AT91C_BASE_CCFG + CCFG_EBICSA) | AT91C_EBI_CS3A_SM,
           AT91C_BASE_CCFG + CCFG_EBICSA);

    /*
     * Configure SMC CS3 
     */
    writel((AT91C_SM_NWE_SETUP | AT91C_SM_NCS_WR_SETUP | AT91C_SM_NRD_SETUP |
            AT91C_SM_NCS_RD_SETUP), AT91C_BASE_SMC + SMC_SETUP3);
    writel((AT91C_SM_NWE_PULSE | AT91C_SM_NCS_WR_PULSE | AT91C_SM_NRD_PULSE |
            AT91C_SM_NCS_RD_PULSE), AT91C_BASE_SMC + SMC_PULSE3);
    writel((AT91C_SM_NWE_CYCLE | AT91C_SM_NRD_CYCLE),
           AT91C_BASE_SMC + SMC_CYCLE3);
    writel((AT91C_SMC_READMODE | AT91C_SMC_WRITEMODE |
            AT91C_SMC_NWAITM_NWAIT_DISABLE | AT91C_SMC_DBW_WIDTH_EIGTH_BITS |
            AT91C_SM_TDF), AT91C_BASE_SMC + SMC_CTRL3);

    /*
     * Configure the PIO controller 
     */
    writel((1 << AT91C_ID_PIOC), PMC_PCER + AT91C_BASE_PMC);

    writel(1 << 13, AT91C_BASE_PIOC + PIO_IFDR(0));
    writel(1 << 13, AT91C_BASE_PIOC + PIO_PPUER(0));
    writel(1 << 13, AT91C_BASE_PIOC + PIO_ODR(0));
    writel(1 << 14, AT91C_BASE_PIOC + PIO_CODR(0));
    writel(1 << 14, AT91C_BASE_PIOC + PIO_MDDR(0));
    writel(1 << 14, AT91C_BASE_PIOC + PIO_PPUDR(0));
    writel(1 << 14, AT91C_BASE_PIOC + PIO_OER(0));
    writel(3 << 13, AT91C_BASE_PIOC + PIO_IDR(0));
    writel(3 << 13, AT91C_BASE_PIOC + PIO_PER(0));
}

#ifdef CFG_HW_INIT
/*----------------------------------------------------------------------------*/
/* \fn    hw_init							      */
/* \brief This function performs very low level HW initialization	      */
/* This function is invoked as soon as possible during the c_startup	      */
/* The bss segment must be initialized					      */
/*----------------------------------------------------------------------------*/
void hw_init(void)
{
    /*
     * Disable watchdog 
     */
    writel(AT91C_WDTC_WDDIS, AT91C_BASE_WDTC + WDTC_WDMR);

    /*
     * At this stage the main oscillator is supposed to be enabled
     * * PCK = MCK = MOSC 
     */

    /*
     * Configure PLLA = MOSC * (PLL_MULA + 1) / PLL_DIVA 
     */
    pmc_cfg_plla(PLLA_SETTINGS, PLL_LOCK_TIMEOUT);

    /*
     * Switch MCK on PLLA output PCK = PLLA = 2 * MCK 
     */
    pmc_cfg_mck(MCKR_SETTINGS, PLL_LOCK_TIMEOUT);

    /*
     * Configure PLLB 
     */
    pmc_cfg_pllb(PLLB_SETTINGS, PLL_LOCK_TIMEOUT);

    /*
     * Configure the PIO controller 
     */
    writel(3 << 14, AT91C_BASE_PIOB + PIO_ASR(0));
    writel(3 << 14, AT91C_BASE_PIOB + PIO_PDR(0));

#ifdef CFG_DEBUG
    /*
     * Enable Debug messages on the DBGU 
     */
    dbg_init(BAUDRATE(MASTER_CLOCK, 115200));

    dbg_print("AT91 bootstrap loading from 0x8400\n\r");
#endif                          /* CFG_DEBUG */

#ifdef CFG_SDRAM
    /*
     * Initialize the matrix 
     */
    writel(readl(AT91C_BASE_CCFG + CCFG_EBICSA) | AT91C_EBI_CS1A_SDRAMC,
           AT91C_BASE_CCFG + CCFG_EBICSA);

    /*
     * Configure SDRAM Controller 
     */

#define HYNIX

//#define MICRON
#ifdef MICRON
#define MICRON_REFRESH 1420     /* 15.625 us / 11 ns @ 180 Mhz */
    sdram_init(AT91C_SDRAMC_NC_9 | AT91C_SDRAMC_NR_12 | AT91C_SDRAMC_CAS_2 | AT91C_SDRAMC_NB_4_BANKS | AT91C_SDRAMC_DBW_32_BITS | AT91C_SDRAMC_TWR_2 |  // 1 CLK+7ns
               AT91C_SDRAMC_TRC_7 |     // 60 ns
               AT91C_SDRAMC_TRP_3 |     // 15 ns
               AT91C_SDRAMC_TRCD_3 |    // 15 ns
               AT91C_SDRAMC_TRAS_7 |    // 37-120 ns
               AT91C_SDRAMC_TXSR_7,     /* 67ns *//* Control Register */
               /*
                * 600 700 735 
                */ MICRON_REFRESH /* 740 1536 */ );     /* Refresh Timer Register */

#endif
/* 
HY57V561620BT-H
     *CAS lat		*tRCD		*tRAS		*tRC		*tRP		tAC	tOH
133	2		2		6		8		2		5.4ns	2.7ns
125	3		3		6		9		3		6ns	3ns
100	2		2		5		7		2		6ns	3ns

*/
#ifdef HYNIX
#if defined(PLLA_180MHz)
/* CLK= 11ns */
/* TWR = tDPL = 2 2CLK always */
/* TRC = tRC = 65ns = 6 clk */
/* TRP = tRP = 20ns = 2 clk */
/* TRCD = tRCD = 20ns = 2 clk */
/* TRAS = tRAS = 45ns = 5 clk */
/* TXSR = tRRC = 65ns = 6 clk */

    sdram_init(AT91C_SDRAMC_NC_9 | AT91C_SDRAMC_NR_13 | AT91C_SDRAMC_CAS_2 | AT91C_SDRAMC_NB_4_BANKS | AT91C_SDRAMC_DBW_32_BITS | AT91C_SDRAMC_TWR_2 | AT91C_SDRAMC_TRC_6 |     /* *7 */
               AT91C_SDRAMC_TRP_2 | AT91C_SDRAMC_TRCD_2 | AT91C_SDRAMC_TRAS_5 | /* *5 */
               AT91C_SDRAMC_TXSR_6,     /* *8 *//* Control Register */
               710);            /* Refresh Timer Register */

#elif defined(PLLA_120MHz)
/* CLK= 16ns, MCLK=60MHz */
/* TWR = tDPL = 2 2CLK always */
/* TRC = tRC = 65ns = 4 clk */
/* TRP = tRP = 20ns = 2 clk */
/* TRCD = tRCD = 20ns = 2 clk */
/* TRAS = tRAS = 45ns = 3 clk */
/* TXSR = tRRC = 65ns = 4 clk */

    sdram_init(AT91C_SDRAMC_NC_9 | AT91C_SDRAMC_NR_13 | AT91C_SDRAMC_CAS_2 | AT91C_SDRAMC_NB_4_BANKS | AT91C_SDRAMC_DBW_32_BITS | AT91C_SDRAMC_TWR_2 | AT91C_SDRAMC_TRC_4 | AT91C_SDRAMC_TRP_2 | AT91C_SDRAMC_TRCD_2 | AT91C_SDRAMC_TRAS_3 |    /* *5 */
               AT91C_SDRAMC_TXSR_4,     /* *8 *//* Control Register */
               1032);           /* Refresh Timer Register */
#else
#error define PLLA180MHz
#endif
#endif                          /* HYNIX */
#endif                          /* CFG_SDRAM */

#ifdef	CFG_FLASH
    flash_hw_init();
#endif
    nandflash_hw_init();
}
#endif                          /* CFG_HW_INIT */

#ifdef CFG_SDRAM
/*------------------------------------------------------------------------------*/
/* \fn    sdramc_hw_init							*/
/* \brief This function performs SDRAMC HW initialization			*/
/*------------------------------------------------------------------------------*/
void sdramc_hw_init(void)
{
    writel(0xFFFF0000, AT91C_BASE_PIOC + PIO_ASR(0));
    writel(0xFFFF0000, AT91C_BASE_PIOC + PIO_PDR(0));

}
#endif                          /* CFG_SDRAM */

#ifdef CFG_DATAFLASH

/*------------------------------------------------------------------------------*/
/* \fn    df_hw_init								*/
/* \brief This function performs DataFlash HW initialization			*/
/*------------------------------------------------------------------------------*/
void df_hw_init(void)
{
    writel(0xf, 0xfffff444);
    writel(0xf, 0xfffff460);
    writel(0xf, 0xfffff470);
    writel(0xf, 0xfffff404);
    writel(1 << 11, AT91C_BASE_PIOC + PIO_BSR(0));
    writel(1 << 11, AT91C_BASE_PIOC + PIO_PDR(0));
}
#endif                          /* CFG_DATAFLASH */
