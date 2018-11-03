ifeq ($(TYPE),arm)
	EXCLUDE_SRC=$(shell find ./stdlib -name "*.c") $(shell find ./stdlib -name "*.arm.S")
endif