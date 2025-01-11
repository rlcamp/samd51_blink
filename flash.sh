#!/bin/bash
set -euo pipefail

# if bossac is not in path, try to find it where arduino puts it
if command -v bossac; then BOSSAC=bossac;
elif [ -x ${HOME}/Downloads/BOSSA/bin/bossac ]; then
    BOSSAC=${HOME}/Downloads/BOSSA/bin/bossac
elif [ -d ${HOME}/Library/Arduino15/packages/adafruit/tools/ ]; then
    BOSSAC=$(find ${HOME}/Library/Arduino15/packages/adafruit/tools/bossac -type f -name bossac)
fi

if [ $# -ne 2 ]; then
    printf "Usage: ./flash.sh file.bin /dev/cu.usbmodem14501\n"
    exit -1
fi

$BOSSAC -i -d --port=$2 -U -i --offset=0x4000 -w -v $1 -R
