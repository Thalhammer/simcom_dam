SELF_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

SRC ?= $(shell find . -name "*.c") $(shell find . -name "*.arm.S")
OBJ = $(SRC:=.o)

DAM_INC_BASE=$(SELF_DIR)../api/include

OUTNAME=$(OUTPUT_PATH)/cust_app

CC=$(ARM_TOOLCHAIN)/armcc
LINK=$(ARM_TOOLCHAIN)/armlink
FROMELF=$(ARM_TOOLCHAIN)/fromelf

FLAGS += -DT_ARM -D__RVCT__ -D_ARM_ASM_ -DQAPI_TXM_MODULE -DTXM_MODULE -DTX_ENABLE_PROFILING -DTX_ENABLE_EVENT_TRACE -DTX_DISABLE_NOTIFY_CALLBACKS -DTX_DAM_QC_CUSTOMIZATIONS -DTARGET_THREADX -D__SIMCOM_DAM__
FLAGS += -O1 --diag_suppress=9931 --diag_error=warning --cpu=Cortex-A7 --protect_stack --arm_only --apcs=/interwork --c99
CFLAGS +=
CXXFLAGS +=
INC_PATHS +=-I $(DAM_INC_BASE) -I $(DAM_INC_BASE)/threadx_api -I $(DAM_INC_BASE)/qapi

include $(SELF_DIR)config.mk
-include config.mk
-include $(SELF_DIR)usrconfig.mk
-include usrconfig.mk

.PHONY: all clean upload

all: $(OUTNAME).bin

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
	@$(FROMELF) --bincombined $< --output $@

$(OUTNAME).elf: $(OBJ)
	@mkdir -p $(OUTPUT_PATH)
	@echo Linking $@
	@$(LINK) -d -o $@ --elf --ro 0x42000000 --first=txm_module_preamble.arm.S.o --entry=_txm_module_thread_shell_entry --map --no_remove --symbols --list $(OUTNAME).map $^ $(SELF_DIR)common/bin/lib.a "$(SELF_DIR)common/bin/lib.a(txm_module_preamble.arm.S.o)"

%.c.o: %.c
	@mkdir -p `dirname $(DEP_DIR)/$@.d`
	@echo Building $<
	@$(CC) -c $(FLAGS) $(CFLAGS) $(INC_PATHS) $< -o $@ --depend=$(DEP_DIR)/$@.d

%.S.o: %.pp.S
	@echo Building $<
	@$(CC) -c $(FLAGS) $(CFLAGS) $(INC_PATHS) $< -o $@

%.pp.S: %.S
	@echo Building $<
	@$(CC) -E $(FLAGS) $(CFLAGS) $(INC_PATHS) $< > $@

-include $(OBJ:%=$(DEP_DIR)/%.d)