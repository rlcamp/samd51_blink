ifndef USE_ARDUINO
    PATH_CC:=$(shell find ${HOME} -maxdepth 2 -type d -name 'arm-gnu-toolchain*' 2>/dev/null | sort | tail -n1)/bin/
# to use this, download generic arm-none-eabi-gcc, cmsis, cmsis-atmel, download and compile bossac
    PATH_CMSIS:=$(shell find ${HOME} -maxdepth 2 -type d -name 'CMSIS_5' 2>/dev/null)/CMSIS/
    PATH_ATMEL:=$(shell find ${HOME} -maxdepth 2 -type d -name 'Atmel.SAMD51_DFP.*' 2>/dev/null | sort | tail -n1)/samd51a/include
else
    PATH_CC:=$(shell find ${HOME}/Library/Arduino15/packages/adafruit/tools/arm-none-eabi-gcc/ -type d -name bin | sort | tail -n1)
    PATH_CMSIS:=$(shell find ${HOME}/Library/Arduino15/packages/adafruit/tools/CMSIS/ -type d -mindepth 2 -maxdepth 2 -name 'CMSIS')
    PATH_ATMEL:=$(shell find ${HOME}/Library/Arduino15/packages/adafruit/tools/CMSIS-Atmel/ -name CMSIS -mindepth 2 -maxdepth 2)/Device/ATMEL/samd51/include
endif

CC=${PATH_CC}/arm-none-eabi-gcc
OBJCOPY=${PATH_CC}/arm-none-eabi-objcopy
AR=${PATH_CC}/arm-none-eabi-gcc-ar

CFLAGS?=-O2

TARGET_ARCH?=-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16

CPPFLAGS?=-Wall -Wextra -Wshadow -Wmissing-prototypes -Wstack-usage=128

# specifying CPPFLAGS at the command line does not affect whether these are appended
# board specific
#override CPPFLAGS+=-D__SAMD51G19A__ -DCRYSTALLESS -DADAFRUIT_ITSYBITSY_M4_EXPRESS -DARDUINO_ITSYBITSY_M4 -DUSB_VID=0x239A -DUSB_PID=0x802B -DUSBCON -DUSB_CONFIG_POWER=100 -DVARIANT_QSPI_BAUD_DEFAULT=50000000 -DUSB_MANUFACTURER="Adafruit" -DUSB_PRODUCT="ItsyBitsy M4"
override CPPFLAGS+=-DARDUINO_FEATHER_M4 -D__SAMD51J19A__ -DADAFRUIT_FEATHER_M4_EXPRESS -DUSB_VID=0x239A -DUSB_PID=0x8022 -DUSBCON -DUSB_CONFIG_POWER=100 -DUSB_MANUFACTURER=Adafruit -DUSB_PRODUCT=Feather
# common
override CPPFLAGS+=-D__SKETCH_NAME__=blink -DF_CPU=48000000L -DARDUINO_ARCH_SAMD -DARDUINO_SAMD_ADAFRUIT -D__SAMD51__ -D__FPU_PRESENT -DARM_MATH_CM4 -DENABLE_CACHE -DVARIANT_QSPI_BAUD_DEFAULT=50000000 -I${PATH_CMSIS}/Core/Include/ -I${PATH_ATMEL}

LDLIBS=-nostdlib -lm -lgcc -lc_nano -lnosys

# using := here ensures that the value of CFLAGS is prepended to LDFLAGS BEFORE the additional things below are appended to CFLAGS
LDFLAGS:=${CFLAGS} -Wl,--gc-sections -Tflash_with_bootloader.ld -Wl,--check-sections -Wl,--unresolved-symbols=report-all -Wl,--warn-common

# specifying CFLAGS at the command line does not affect whether these are appended
override CFLAGS+=-ffunction-sections -fdata-sections --param max-inline-insns-single=500

TARGETS=samd51_blink.bin

all : ${TARGETS}

# implicit rule requires this to have no extension, but it is logically an .elf file
samd51_blink : samd51_blink.o samd51_init.o

samd51_blink.bin : samd51_blink
	${OBJCOPY} -O binary $< $@

.PHONY: clean
clean :
	$(RM) *.o *.a $(shell find . -maxdepth 1 -type f ! -name "*.*" | grep -v Makefile) ${TARGETS}

*.o : Makefile
