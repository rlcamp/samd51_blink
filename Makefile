ifndef USE_ARDUINO
# to use this, download generic arm-none-eabi-gcc, cmsis, cmsis-atmel, download and compile bossac
    CC=$(shell find ${HOME}/Downloads/arm-gnu-toolchain-*-arm-none-eabi/bin/ -type f -name arm-none-eabi-gcc)
    OBJCOPY=$(shell find ${HOME}/Downloads/arm-gnu-toolchain-*-arm-none-eabi/bin/ -type f -name arm-none-eabi-objcopy)
    PATH_CMSIS=${HOME}/Downloads/CMSIS_5/CMSIS/
    PATH_ATMEL=$(shell find ${HOME}/Downloads/Atmel.SAMD51_DFP.* -name include -mindepth 2 -maxdepth 2)
# this is the only thing explicitly needed from adafruit, and only so we don't accidentally overwrite the uf2 bootloader
    PATH_LINKER_SCRIPT=flash_with_bootloader.ld
else
    CC=$(shell find ${HOME}/Library/Arduino15/packages/adafruit/tools/arm-none-eabi-gcc/ -type f -name arm-none-eabi-gcc)
    OBJCOPY=$(shell find ${HOME}/Library/Arduino15/packages/adafruit/tools/arm-none-eabi-gcc/ -type f -name arm-none-eabi-objcopy)
    PATH_CMSIS=$(shell find ${HOME}/Library/Arduino15/packages/adafruit/tools/CMSIS/ -type d -mindepth 2 -maxdepth 2 -name 'CMSIS')
    PATH_ATMEL=$(shell find ${HOME}/Library/Arduino15/packages/adafruit/tools/CMSIS-Atmel/ -name include -mindepth 6 -maxdepth 6 | grep samd51)
    PATH_LINKER_SCRIPT=$(shell find ${HOME}/Library/Arduino15/packages/adafruit/hardware/samd/ | grep 'variants/feather_m4/linker_scripts/gcc/flash_with_bootloader.ld')
endif

OPTFLAGS=-Os

TARGET_ARCH=-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
CPPFLAGS=-D__SKETCH_NAME__=blink -DF_CPU=120000000L -DNON_ANCIENT_HEADER_PATHS -DARDUINO_FEATHER_M4 -DARDUINO_ARCH_SAMD -DARDUINO_SAMD_ADAFRUIT -D__SAMD51J19A__ -DADAFRUIT_FEATHER_M4_EXPRESS -D__SAMD51__ -DUSB_VID=0x239A -DUSB_PID=0x8022 -DUSBCON -DUSB_CONFIG_POWER=100 -DUSB_MANUFACTURER=Adafruit -DUSB_PRODUCT=Feather -D__FPU_PRESENT -DARM_MATH_CM4 -DENABLE_CACHE -DVARIANT_QSPI_BAUD_DEFAULT=50000000

CFLAGS=${OPTFLAGS} -Wall -Wextra -Wno-expansion-to-defined -std=gnu11 -ffunction-sections -fdata-sections --param max-inline-insns-single=500 -I${PATH_CMSIS}/Core/Include/ -I${PATH_ATMEL} -I${PATH_ATMEL}/samd51/include/

LDLIBS=-nostdlib -lm -lgcc -lc_nano -lnosys

LDFLAGS=${OPTFLAGS} -Wl,--gc-sections -T${PATH_LINKER_SCRIPT} -Wl,--check-sections -Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-section-align

TARGETS=samd51_blink.bin

all : ${TARGETS}

# implicit rule requires this to have no extension, but it is logically an .elf file
samd51_blink : samd51_blink.o samd51_init.o

samd51_blink.bin : samd51_blink
	${OBJCOPY} -O binary $< $@

.PHONY: clean
clean :
	$(RM) *.o $(shell find . -type f -maxdepth 1 ! -name "*.*" | grep -v Makefile) ${TARGETS}

*.o : Makefile
