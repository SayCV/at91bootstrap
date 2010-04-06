# Makefile for AT91-Bootstrap drivers directory
# DIRS				+= drivers

DRIVERS:=
DRIVERS_SRC:=$(TOPDIR)/driver/

COBJS-y				+=	$(DRIVERS_SRC)debug.o
COBJS-y				+=	$(DRIVERS_SRC)gpio.o
COBJS-y				+=	$(DRIVERS_SRC)pmc.o

COBJS-$(CONFIG_SDRAM)		+=	$(DRIVERS_SRC)sdramc.o
COBJS-$(CONFIG_SDDRC)		+=	$(DRIVERS_SRC)sddrc.o
COBJS-$(CONFIG_DDR2)		+=	$(DRIVERS_SRC)ddramc.o

COBJS-$(CONFIG_DATAFLASH)	+=	$(DRIVERS_SRC)dataflash.o
COBJS-$(CONFIG_FLASH)		+=	$(DRIVERS_SRC)flash.o
COBJS-$(CONFIG_NANDFLASH)	+=	$(DRIVERS_SRC)nandflash.o
COBJS-$(CONFIG_USER_HW_INIT)	+=	$(DRIVERS_SRC)user_hw_init.o
