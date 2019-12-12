SELF_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
CROSSTOOLS_PATH = /opt/gcc-arm-none-eabi-9-2019-q4-major/bin/
CC = $(CROSSTOOLS_PATH)arm-none-eabi-gcc
CXX = $(CROSSTOOLS_PATH)arm-none-eabi-g++
AR = $(CROSSTOOLS_PATH)arm-none-eabi-ar

SRC ?= $(shell find . -name "*.c") $(shell find . -name "*.cpp") $(shell find . -name "*.cc") $(shell find . -name "*.S")
EXCLUDE_SRC =
FSRC = $(filter-out $(EXCLUDE_SRC), $(SRC))
OBJ = $(FSRC:=.o)

OUTNAME=libc.a

FLAGS += -O2 -Wall -Wextra -Werror -nostdlib -nostdinc -ffunction-sections -fdata-sections
FLAGS += -fno-omit-frame-pointer -mcpu=cortex-a7 -marm -mno-unaligned-access -mfloat-abi=soft
CFLAGS += -std=c11
CXXFLAGS += --std=c++17 -fno-exceptions -fno-rtti
INC_PATHS +=-I $(SELF_DIR)/../libc/include

DEP_DIR := .deps

.PHONY: all clean

all: $(OUTNAME)

clean:
	@echo "Cleaning..."
	@rm -rf $(OUTNAME)
	@rm -f $(OBJ)
	@rm -rf $(DEP_DIR)
	@echo "Done."

$(OUTNAME): $(OBJ)
	@echo Generating $@
	@$(AR) rcs $@ $^

%.c.o: %.c
	@echo Building $<
	@$(CC) -c $(FLAGS) $(CFLAGS) $(INC_PATHS) $< -o $@
	@mkdir -p `dirname $(DEP_DIR)/$@.d`
	@$(CC) -c $(FLAGS) $(CFLAGS) $(INC_PATHS) -MT '$@' -MM $< > $(DEP_DIR)/$@.d

%.cpp.o: %.cpp
	@echo Building $<
	@$(CXX) -c $(FLAGS) $(CXXFLAGS) $(INC_PATHS) $< -o $@
	@mkdir -p `dirname $(DEP_DIR)/$@.d`
	@$(CXX) -c $(FLAGS) $(CXXFLAGS) $(INC_PATHS) -MT '$@' -MM $< > $(DEP_DIR)/$@.d

%.cc.o: %.cc
	@echo Building $<
	@$(CXX) -c $(FLAGS) $(CXXFLAGS) $(INC_PATHS) $< -o $@
	@mkdir -p `dirname $(DEP_DIR)/$@.d`
	@$(CXX) -c $(FLAGS) $(CXXFLAGS) $(INC_PATHS) -MT '$@' -MM $< > $(DEP_DIR)/$@.d

%.S.o: %.S
	@echo Building $<
	@$(CC) -c $(FLAGS) $(CFLAGS) $(INC_PATHS) $< -o $@

-include $(OBJ:%=$(DEP_DIR)/%.d)