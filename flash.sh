#!/bin/bash
set -euo pipefail

if true; then
    BOSSAC=${HOME}/Downloads/BOSSA/bin/bossac
    OBJCOPY=${HOME}/Downloads/arm-gnu-toolchain-11.3.rel1-darwin-x86_64-arm-none-eabi/bin/arm-none-eabi-objcopy
else
    OBJCOPY=${HOME}/Library/Arduino15/packages/adafruit/tools/arm-none-eabi-gcc/9-2019q4/bin/arm-none-eabi-objcopy
    BOSSAC=${HOME}/Library/Arduino15/packages/arduino/tools/bossac/1.8.0-48-gb176eee/bossac
fi

if [ $# -eq 2 ]; then
# if a command line argument was given, assume it is the /dev/cu.whatever corresponding to the device as it appears when sitting in the uf2 bootloader
    stty speed 1200 < $2
    ${OBJCOPY} -O binary $1 /tmp/tmp.bin
    sleep 1
    ${BOSSAC} -i -d --port=$2 -U -i --offset=0x4000 -w -v /tmp/tmp.bin -R
else
    printf "Usage: ./flash.sh file.elf /dev/cu.usbmodem14501\n"
fi
