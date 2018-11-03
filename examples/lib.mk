SELF_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
ifeq ($(TYPE), gcc)
include $(SELF_DIR)/lib.gcc.mk
else
include $(SELF_DIR)/lib.arm.mk
endif