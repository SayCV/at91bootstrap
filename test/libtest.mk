# Makefile for AT91Bootstrap libtest directory
# DIRS				+= libtest

LIBTEST:=$(TOPDIR)/test

COBJS-y		+= $(LIBTEST)/testHelper.o

COBJS-y		+= $(LIBTEST)/cfi_flash.o

COBJS-y		+= $(LIBTEST)/cfi_flash_amd.o

COBJS-y		+= $(LIBTEST)/test-DDR2.o
COBJS-y		+= $(LIBTEST)/test-LED.o
COBJS-y		+= $(LIBTEST)/test-NAND.o
COBJS-y		+= $(LIBTEST)/test-NOR.o
COBJS-y		+= $(LIBTEST)/test-YC.o
COBJS-y		+= $(LIBTEST)/test-YKYX.o

#COBJS-$(CONFIG_OF_LIBFDT) += $(LIBC)/fdt.o
