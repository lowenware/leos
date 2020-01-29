#
# build.mk
# Ilja Kartašov, 2019-11-29 17:38
#

include ${ROOT}kernel/config.mk

BUILD_DIR ?= build/

AARCH64_TOOLCHAIN ?= aarch64-linux-gnu
AARCH64_CC = clang --target=aarch64-none-elf -mcpu=cortex-a57
AARCH64_LD = ld.lld
AARCH64_OBJCOPY = $(AARCH64_TOOLCHAIN)-objcopy --target elf64-littleaarch64

AARCH64_QEMU = \
  qemu-system-aarch64 \
    -M virt \
    -cpu cortex-a53 \
    -nographic \
    -smp 4 \
    -m 4096 \
    -kernel build/kernel/kernel.elf \
    -serial stdio \
    -monitor none \

 AARCH64_QEMU = \
  qemu-system-aarch64 \
    -M raspi3 \
    -nographic \
    -kernel build/kernel/kernel.elf \
    -serial /dev/null \
    -serial stdio \
    -monitor none \

#    -kernel /home/elias/git/rpi/boards/pi3/aarch64/uart02/kernel8.img \
# vim:ft=make
#

CONFIG_CFLAGS = -D"CONFIG_ARCH=\"${CONFIG_ARCH}\""
CONFIG_CFLAGS = -DCONFIG_ARM_TIMER=${CONFIG_ARM_TIMER}

#ifeq (${CONFIG_HARDWARE}, rpi3)
#CONFIG_CFLAGS += -DCONFIG_HARDWARE_RPI3=1
#else ifeq (${CONFIG_HARDWARE}, qemu)
#CONFIG_CFLAGS += -DCONFIG_HARDWARE_QEMU=1
#endif
