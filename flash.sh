#!/bin/bash
set -euo pipefail

if [ ! -x ${HOME}/Downloads/uf2/utils/uf2conv.py ]; then
    cd ~/Downloads/
    git clone --depth 1 https://github.com/microsoft/uf2.git
    cd -
fi

if [ $# -lt 2 ]; then
    printf "Usage: ./flash.sh file.bin\n"
    exit -1
fi

~/Downloads/uf2/utils/uf2conv.py -b 0x4000 $1
