#!/bin/bash
set -euo pipefail

if true; then
    BOSSAC=${HOME}/Downloads/BOSSA/bin/bossac
else
    BOSSAC=${HOME}/Library/Arduino15/packages/arduino/tools/bossac/1.8.0-48-gb176eee/bossac
fi

if [ $# -eq 2 ]; then
# if a command line argument was given, assume it is the /dev/cu.whatever corresponding to the device as it appears when sitting in the uf2 bootloader
    stty speed 1200 < $2
    sleep 1
    ${BOSSAC} -i -d --port=$2 -U -i --offset=0x4000 -w -v $1 -R
else
    printf "Usage: ./flash.sh file.bin /dev/cu.usbmodem14501\n"
fi
