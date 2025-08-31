# ===========================
# Toolchain & Directories
# ===========================

# Detect platform
UNAME_S := $(shell uname -s)

ifeq ($(OS),Windows_NT)
    # Windows
    GCC_DIR     := C:/Tools/arm-gcc
    RM          := del /Q
    MKDIR       := mkdir
    PROG_CLI    := "C:/Program Files/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin/STM32_Programmer_CLI.exe"
else
    # Linux / WSL
    GCC_DIR     := /usr
    RM          := rm -f
    MKDIR       := mkdir -p
    PROG_CLI    := "/mnt/c/Program Files/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin/STM32_Programmer_CLI.exe"
endif

OBJ_COPY    := $(GCC_DIR)/bin/arm-none-eabi-objcopy
CC          := $(GCC_DIR)/bin/arm-none-eabi-gcc
OUTPUT_DIR  := ./output
LINKER_DIR  := ./linker

# ===========================
# Include files
# ===========================
INC_DIRS    := ./core ./system ./driver/inc ./module ./tasks
INC_FILES   := $(foreach INC_DIR, $(INC_DIRS), $(wildcard $(INC_DIR)/*))

# ===========================
# Source files
# ===========================
SRC_DIRS    := ./core ./driver/src ./startup ./module ./tasks
SRC_FILES   := $(foreach SRC_DIR, $(SRC_DIRS), $(wildcard $(SRC_DIR)/*.c))

# Object files
OBJ_FILES   := $(patsubst %.c, %.o, $(notdir $(SRC_FILES)))
OBJ_PATHS   := $(patsubst %.c, $(OUTPUT_DIR)/%.o, $(notdir $(SRC_FILES)))

# ===========================
# Options
# ===========================
INC_DIRS_OPT := $(foreach INC_DIR, $(INC_DIRS), -I$(INC_DIR))
CHIP         := cortex-m3
CCFLAGS      := -c -mcpu=$(CHIP) -mthumb -std=gnu11 -O0 $(INC_DIRS_OPT)
LDFLAGS      := -nostdlib -T $(LINKER_DIR)/stm32_ls.ld -Wl,-Map=$(OUTPUT_DIR)/makefile.map

# ===========================
# Colors
# ===========================
RESET  := \033[0m
YELLOW := \033[1;33m
CYAN   := \033[36m
GREEN  := \033[0;32m
MAGENTA := \033[35m
BLUE   := \033[0;34m
RED    := \033[0;31m

# ===========================
# Rules
# ===========================
vpath %.c $(SRC_DIRS)

build: $(OUTPUT_DIR)/makefile.hex

print-%:
	@printf "%s\n" $($(subst print-,,$@))

clear:
	@printf "$(YELLOW)[CLEAR]$(RESET) Removing build files...\n"
	@$(RM) $(OUTPUT_DIR)/*

# ensure output dir exists
$(OUTPUT_DIR):
	@$(MKDIR) $(OUTPUT_DIR)

$(OUTPUT_DIR)/%.o: %.c | $(OUTPUT_DIR)
	@printf "$(GREEN)[CC]$(RESET) %-30s -> $@\n" $<
	@$(CC) $(CCFLAGS) -o $@ $<

makefile.elf: $(OBJ_PATHS)
	@printf "$(BLUE)[LD]$(RESET) Linking objects...\n"
	@$(CC) $(LDFLAGS) -o $(OUTPUT_DIR)/$@ $(OBJ_PATHS)

$(OUTPUT_DIR)/makefile.hex: makefile.elf
	@printf "$(BLUE)[OBJCOPY]$(RESET) Generating HEX...\n"
	@$(OBJ_COPY) -O ihex $(OUTPUT_DIR)/makefile.elf $(OUTPUT_DIR)/makefile.hex

upload: $(OUTPUT_DIR)/makefile.hex
	@printf "$(YELLOW)[UPLOAD]$(RESET) Flashing firmware...\n"
	@$(PROG_CLI) -c port=SWD -d $(OUTPUT_DIR)/makefile.hex 0x08000000 -rst
	@printf "$(GREEN)==========  Upload Success!  ==========$(RESET)\n"

erase: 
	@printf "$(YELLOW)[ERASE]$(RESET) Chip erase...\n"
	@$(PROG_CLI) -c port=SWD -e all -rst
	@printf "$(GREEN)==========  Erase Success!  ==========$(RESET)\n"

reset:
	@printf "$(YELLOW)[RESET]$(RESET) Resetting MCU...\n"
	@$(PROG_CLI) -c port=SWD -rst
	@printf "$(GREEN)==========  Reset Success!  ==========$(RESET)\n"

# ========================
# Tree command
# ========================
.PHONY: tree
tree:
	@printf "$(YELLOW)[TREE]$(RESET) Project structure:\n"
	@tree -C --dirsfirst \
		--noreport \
		--dirsfirst \
		-I '.git|build|*.o' \
		| sed -E "s/([[:digit:]]+ directories, [[:digit:]]+ files)/$(GREEN)\1$(RESET)/"

.PHONY: build clear upload erase reset
