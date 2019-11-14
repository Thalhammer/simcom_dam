SELF_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
VALID_TYPES= arm gcc
ifeq ($(TYPE), )
TYPE=gcc
endif
ifeq ($(filter $(TYPE),$(VALID_TYPES)),)
$(warning !!! Invalid TYPE, setting gcc !!!)
TYPE=gcc
endif
ifeq ($(TYPE), gcc)
include $(SELF_DIR)/lib.gcc.mk
else
include $(SELF_DIR)/lib.arm.mk
endif