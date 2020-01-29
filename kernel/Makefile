# environment

ROOT = ../

include ${ROOT}Makevars.mk

# CFLAGS

CFLAGS += -O0
CFLAGS += -g
CFLAGS += -nostdlib
CFLAGS += -march=armv8-a
# CFLAGS += -std=c99
# CFLAGS += -pedantic
CFLAGS += -Wall
CFLAGS += -Wmissing-prototypes
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wold-style-definition

INCS += -I./

# SOURCES

LD_SCRIPT = aarch64/aarch64.ld

SOURCE_FILES = \
	aarch64/aarch64_boot.S \
	aarch64/aarch64.S \
	\
	leos/irq.c \
	leos/leos.c \
	leos/log.c \
	leos/memory.c \
	leos/task.c \
	\
	drivers/timer/timer.c \
	drivers/uart/uart_mini.c \
	drivers/uart/uart_qemu.c \

SOURCE_LIST  := $(wildcard $(SOURCE_FILES))
OBJECT_FILES := $(addsuffix .o, $(addprefix $(BUILD_DIR), ${SOURCE_LIST}))

# rules 

all: kernel

default: kernel

kernel: $(BUILD_DIR)kernel.elf $(BUILD_DIR)kernel.list $(BUILD_DIR)kernel.bin

$(BUILD_DIR)kernel.elf: $(OBJECT_FILES)
	$(info linking target: $@)
	$(AARCH64_LD) -T$(LD_SCRIPT) -nostdlib $^ -o $@
	$(info done: $@)

$(BUILD_DIR)kernel.list: $(BUILD_DIR)kernel.elf
	$(AARCH64_OBJCOPY) -D $(BUILD_DIR)kernel.elf > $@

$(BUILD_DIR)kernel.bin: $(BUILD_DIR)/kernel.elf
	$(AARCH64_OBJCOPY) -O binary $< $@
	cp $@ $(BUILD_DIR)kernel8.img

$(BUILD_DIR)kernel.sym: $(BUILD_DIR)/kernel.elf
	$(AARCH64_OBJCOPY) --only-keep-debug $< $@
	$(AARCH64_OBJCOPY) --strip-debug $@

$(BUILD_DIR)%.o: %
	$(info compiling file: $<)
	@mkdir -p $(dir ./$(BUILD_DIR)$<)
	$(AARCH64_CC) $(INCS) $(CFLAGS) $(CONFIG_CFLAGS) -c $< -o $@

