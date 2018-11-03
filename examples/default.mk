SELF_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
VALID_TYPES= arm gcc
ifeq ($(TYPE), )
	TYPE=arm
endif
ifeq ($(filter $(TYPE),$(VALID_TYPES)),)
	@echo !!! Invalid TYPE, setting arm !!!
	TYPE=arm
endif
ifeq ($(TYPE), gcc)
include $(SELF_DIR)/default.gcc.mk
else
include $(SELF_DIR)/default.arm.mk
endif