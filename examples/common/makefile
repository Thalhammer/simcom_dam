ifeq ($(TYPE), arm)
SRC = $(shell find txm_lib -name "*.c") $(shell find . -name "*.arm.S")
include ../lib.mk
else
include ../lib.gcc.mk
endif