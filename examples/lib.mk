SELF_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
VALID_TYPES= arm gcc
ifeq ($(TYPE), )
TYPE=arm
endif
ifeq ($(filter $(TYPE),$(VALID_TYPES)),)
$(warning !!! Invalid TYPE, setting arm !!!)
TYPE=arm
endif
ifeq ($(TYPE), gcc)
include $(SELF_DIR)/lib.gcc.mk
else
include $(SELF_DIR)/lib.arm.mk
endif