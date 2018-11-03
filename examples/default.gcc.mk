SELF_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

SRC ?= $(shell find . -name "*.c") $(shell find . -name "*.gcc.S")
EXCLUDE_SRC =
FSRC = $(filter-out $(EXCLUDE_SRC), $(SRC))
OBJ = $(FSRC:=.o)

DAM_INC_BASE=$(SELF_DIR)../api/include

OUTNAME=$(OUTPUT_PATH)/cust_app

CC=$(GCC_TOOLCHAIN)/arm-none-eabi-gcc
LINK=$(GCC_TOOLCHAIN)/arm-none-eabi-ld
OBJCOPY=$(GCC_TOOLCHAIN)/arm-none-eabi-objcopy

FLAGS += -DQAPI_TXM_MODULE -DTXM_MODULE -DTX_ENABLE_PROFILING -DTX_ENABLE_EVENT_TRACE -DTX_DISABLE_NOTIFY_CALLBACKS -DTX_DAM_QC_CUSTOMIZATIONS -DTARGET_THREADX -D__SIMCOM_DAM__
FLAGS += -O2 -Wall -mcpu=cortex-a7 -marm -mno-unaligned-access -nostdlib -nostdinc -mfloat-abi=soft
CFLAGS +=
CXXFLAGS +=
INC_PATHS +=-I $(DAM_INC_BASE) -I $(DAM_INC_BASE)/threadx_api -I $(DAM_INC_BASE)/qapi -I $(DAM_INC_BASE)/stdlib

include $(SELF_DIR)config.mk
-include config.mk
-include $(SELF_DIR)usrconfig.mk
-include usrconfig.mk

.PHONY: all clean upload printcfg

all: $(OUTNAME).bin

printcfg:
	@echo "TYPE=            " $(TYPE)
	@echo "SRC=             " $(SRC)
	@echo "EXCLUDE_SRC=     " $(EXCLUDE_SRC)
	@echo "Filtered SRC=    " $(FSRC)
	@echo "Includes=        " $(INC_PATHS)
	@echo "FLAGS=           " $(FLAGS)
	@echo "CFLAGS=          " $(CFLAGS)
	@echo "CXXFLAGS=        " $(CXXFLAGS)
	@echo "CC=              " $(CC)
	@echo "LINK=            " $(LINK)
	@echo "OBJCOPY=         " $(OBJCOPY)

clean:
	@echo "Cleaning..."
	@rm -rf $(OUTPUT_PATH)
	@rm -f $(OBJ)
	@rm -rf $(DEP_DIR)
	@echo "Done."

upload: $(OUTNAME).bin
	@sudo ../../tools/upload $(UPLOAD_DEV) $(OUTNAME).bin

$(OUTNAME).bin: $(OUTNAME).elf
	@echo Generating $@
	@$(OBJCOPY) -O binary --only-section=ER_RO --only-section=ER_RW $^ $@

$(OUTNAME).elf: $(OBJ)
	@mkdir -p $(OUTPUT_PATH)
	@echo Linking $@
	@$(LINK) -o $@ -e _txm_module_thread_shell_entry -T ../common/linker.lds --entry=__txm_module_preamble -Map=$(OUTNAME).map $^ $(SELF_DIR)/common/bin/lib.a -gc-sections

%.c.o: %.c
	@echo Building $<
	@$(CC) -c $(FLAGS) $(CFLAGS) $(INC_PATHS) $< -o $@
	@mkdir -p `dirname $(DEP_DIR)/$@.d`
	@$(CC) -c $(FLAGS) $(CFLAGS) $(INC_PATHS) -MT '$@' -MM $< > $(DEP_DIR)/$@.d

%.S.o: %.pp.S
	@echo Building $<
	@$(CC) -c $(FLAGS) $(CFLAGS) $(INC_PATHS) $< -o $@

%.pp.S: %.S
	@echo Building $<
	@$(CC) -E $(FLAGS) $(CFLAGS) $(INC_PATHS) $< > $@

-include $(OBJ:%=$(DEP_DIR)/%.d)