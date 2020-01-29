ROOT = ./

include ${ROOT}Makevars.mk

# Rules
#
all: kernel

$(BUILD_DIR)kernel:
	mkdir -p $@

.PHONY: clean run debug kernel

kernel: $(BUILD_DIR)kernel
	cd kernel && BUILD_DIR=../$(BUILD_DIR)kernel/ make

clean:
	rm -Rf ./$(BUILD_DIR)*

run: kernel
	$(AARCH64_QEMU)

debug: kernel
	$(AARCH64_QEMU) -S -gdb tcp::1234 & \
	gdb-multiarch -q \
	-ex 'file $(BUILD_DIR)kernel/kernel.elf' \
	-ex 'target remote localhost:1234'
	kill %1

console:
	sudo picocom -b 115200 -r -l /dev/ttyUSB0
