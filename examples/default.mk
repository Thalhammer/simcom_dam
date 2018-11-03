SELF_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
ifeq ($(TYPE), gcc)
include $(SELF_DIR)/default.gcc.mk
else
include $(SELF_DIR)/default.arm.mk
endif