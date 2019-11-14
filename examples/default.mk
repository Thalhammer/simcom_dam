SELF_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
VALID_TYPES= arm gcc
DEFAULT_TYPE=gcc
ifeq ($(TYPE), )
	TYPE=$(DEFAULT_TYPE)
endif
ifeq ($(filter $(TYPE),$(VALID_TYPES)),)
	@echo !!! Invalid TYPE, setting $(DEFAULT_TYPE) !!!
	TYPE=$(DEFAULT_TYPE)
endif
ifeq ($(TYPE), gcc)
include $(SELF_DIR)/default.gcc.mk
else
include $(SELF_DIR)/default.arm.mk
endif