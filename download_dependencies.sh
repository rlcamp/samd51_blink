#!/bin/sh
# this script tested working on arm64 macos sequoia provided xz has been compiled from source
set -eu

# the Makefile is going to look for each of these things in ~/Downloads/ unless told otherwise
cd ~/Downloads/

if [ ! -d CMSIS_5 ]; then git clone --depth 1 https://github.com/ARM-software/CMSIS_5 ; fi

if [ ! -d Atmel.SAMD51_DFP.1.2.139 ]; then
    curl -O http://packs.download.atmel.com/Atmel.SAMD51_DFP.1.2.139.atpack
    unzip Atmel.SAMD51_DFP.1.2.139.atpack -d Atmel.SAMD51_DFP.1.2.139
fi

if [ ! -d arm-gnu-toolchain-14.2.*-arm-none-eabi ]; then
    if uname -sm | grep 'Linux x86_64' ; then
        TOOLCHAIN_TARBALL=arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-eabi.tar.xz
    elif uname -sm | grep 'Linux aarch64' ; then
        TOOLCHAIN_TARBALL=arm-gnu-toolchain-14.2.rel1-aarch64-arm-none-eabi.tar.xz
    else
        TOOLCHAIN_TARBALL=arm-gnu-toolchain-14.2.rel1-darwin-arm64-arm-none-eabi.tar.xz
    fi

    curl -LO https://developer.arm.com/-/media/Files/downloads/gnu/14.2.rel1/binrel/"$TOOLCHAIN_TARBALL"
    tar Jxf "$TOOLCHAIN_TARBALL"
fi

if [ ! -d BOSSA ]; then
    git clone --depth 1 https://github.com/shumatech/BOSSA
    make -C BOSSA bossac CXXFLAGS="-Wno-unqualified-std-cast-call" 2>&1 | grep -v found >&2
fi
