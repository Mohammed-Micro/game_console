######################################################################
#  Project
######################################################################


target = main.bin
SRCFILES = main.c vga.c

INCLUDE = ../include
LOAD_SCRIPT = ../stm32f103c8t6.ld

include ../Makefile.incl
