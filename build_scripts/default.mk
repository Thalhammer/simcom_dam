SELF_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

SRC ?= $(shell find . -name "*.c") $(shell find . -name "*.cpp") $(shell find . -name "*.gcc.S")
EXCLUDE_SRC =
FSRC = $(filter-out $(EXCLUDE_SRC), $(SRC))
OBJ = $(FSRC:=.o)

DAM_INC_BASE=$(SELF_DIR)../api/include

OUTNAME=$(OUTPUT_PATH)/cust_app

FLAGS += -DQAPI_TXM_MODULE -DTXM_MODULE -DTX_ENABLE_PROFILING -DTX_ENABLE_EVENT_TRACE -DTX_DISABLE_NOTIFY_CALLBACKS -DTX_DAM_QC_CUSTOMIZATIONS -DTARGET_THREADX -D__SIMCOM_DAM__
FLAGS += -O2 -Wall -Wextra -Werror -mcpu=cortex-a7 -marm -mno-unaligned-access -nostdlib -nostdinc -mfloat-abi=soft -ffunction-sections -fdata-sections -fno-omit-frame-pointer
FLAGS += -mtp=cp15
CFLAGS +=
CXXFLAGS += --std=c++11
INC_PATHS +=-I $(DAM_INC_BASE) -I $(DAM_INC_BASE)/threadx_api -I $(DAM_INC_BASE)/qapi -I $(DAM_INC_BASE)/stdlib -I $(SELF_DIR) -I $(SELF_DIR)../uc++lib/libc/include -I $(SELF_DIR)../uc++lib/libc++/include

include $(SELF_DIR)config.mk
-include config.mk
-include $(SELF_DIR)usrconfig.mk
-include usrconfig.mk

.PHONY: all clean upload printcfg

all: $(OUTNAME).bin

printcfg:
	@echo "SRC=             " $(SRC)
	@echo "EXCLUDE_SRC=     " $(EXCLUDE_SRC)
	@echo "Filtered SRC=    " $(FSRC)
	@echo "Includes=        " $(INC_PATHS)
	@echo "FLAGS=           " $(FLAGS)
	@echo "CFLAGS=          " $(CFLAGS)
	@echo "CXXFLAGS=        " $(CXXFLAGS)
	@echo "CC=              " $(CC)
	@echo "CXX=             " $(CXX)
	@echo "LINK=            " $(LINK)
	@echo "OBJCOPY=         " $(OBJCOPY)
	@echo "SIZE=            " $(SIZE)

clean:
	@echo "Cleaning..."
	@rm -rf $(OUTPUT_PATH)
	@rm -f $(OBJ)
	@rm -rf $(DEP_DIR)
	@echo "Done."

size: $(OUTNAME).elf
	@$(SIZE) $(OUTNAME).elf

upload: $(OUTNAME).bin
	@sudo ../../tools/upload $(UPLOAD_DEV) $(OUTNAME).bin

upload-retry: $(OUTNAME).bin
	@until sudo ../../tools/upload $(UPLOAD_DEV) $(OUTNAME).bin; \
	do \
		sleep 0.5; \
	done;

$(OUTNAME).bin: $(OUTNAME).elf
	@echo Generating $@
	@$(OBJCOPY) -O binary $^ $@

$(OUTNAME).elf: $(OBJ) $(SELF_DIR)/linker.lds $(SELF_DIR)/../api/bin/lib.a
	@mkdir -p $(OUTPUT_PATH)
	@echo Linking $@
	@$(LINK) -o $@ -e _txm_module_thread_shell_entry -T $(SELF_DIR)/linker.lds --entry=__txm_module_preamble -Map=$(OUTNAME).map --start-group $(OBJ) $(SELF_DIR)/../api/bin/lib.a $(LIB_GCC) $(SELF_DIR)/../uc++lib/libc++rt/libc++rt.a  $(SELF_DIR)/../uc++lib/libc++/libc++.a  $(SELF_DIR)/../uc++lib/libc/libc.a --end-group -gc-sections -z defs --print-memory-usage

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

%.S.o: %.pp.S
	@echo Building $<
	@$(CC) -c $(FLAGS) $(CFLAGS) $(INC_PATHS) $< -o $@

%.pp.S: %.S
	@echo Building $<
	@$(CC) -E $(FLAGS) $(CFLAGS) $(INC_PATHS) $< > $@

$(SELF_DIR)/../api/bin/lib.a:
	@+make -C $(SELF_DIR)/../api/

-include $(OBJ:%=$(DEP_DIR)/%.d)