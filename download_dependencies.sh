#!/bin/sh
# this script works on arm64 macos sonoma, as of 20240706, provided xz has been compiled from source

cd ~/Downloads/
rm -rf BOSSA
rm -rf CMSIS_5

git clone --depth 1 https://github.com/ARM-software/CMSIS_5

mkdir -p Atmel.SAMD51_DFP.1.2.139
cd Atmel.SAMD51_DFP.1.2.139
curl -O http://packs.download.atmel.com/Atmel.SAMD51_DFP.1.2.139.atpack
unzip Atmel.SAMD51_DFP.1.2.139.atpack
cd ..

if [ ! -d ~/Downloads/arm-gnu-toolchain-14.2-*-arm-none-eabi ]; then
    if uname -sm | grep 'Linux x86_64' ; then
        curl -LO https://developer.arm.com/-/media/Files/downloads/gnu/14.2.rel1/binrel/arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-eabi.tar.xz
        tar Jxf arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-eabi.tar.xz
    elif uname -sm | grep 'Linux aarch64' ; then
        curl -LO https://developer.arm.com/-/media/Files/downloads/gnu/14.2.rel1/binrel/arm-gnu-toolchain-14.2.rel1-aarch64-arm-none-eabi.tar.xz
        tar Jxf arm-gnu-toolchain-14.2.rel1-aarch64-arm-none-eabi.tar.xz
    else
        curl -LO https://developer.arm.com/-/media/Files/downloads/gnu/14.2.rel1/binrel/arm-gnu-toolchain-14.2.rel1-darwin-arm64-arm-none-eabi.tar.xz
        tar Jxf arm-gnu-toolchain-14.2.rel1-darwin-arm64-arm-none-eabi.tar.xz
    fi
fi

git clone --depth 1 https://github.com/shumatech/BOSSA
cd BOSSA
if c++ -v 2>&1 | grep clang ; then
    make bossac CXXFLAGS="-Wno-error=unqualified-std-cast-call" 2>&1 | grep -v found >&2
else
    make bossac 2>&1 | grep -v found >&2
fi
cd ..
