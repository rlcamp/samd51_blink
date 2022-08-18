#!/bin/bash
# this script works on macos monterey, as of 20220816, provided xz has been compiled from source

cd ~/Downloads/

git clone --depth 1 https://github.com/ARM-software/CMSIS_5

mkdir -p Atmel.SAMD51_DFP.1.2.139
cd Atmel.SAMD51_DFP.1.2.139
curl -O http://packs.download.atmel.com/Atmel.SAMD51_DFP.1.2.139.atpack
unzip Atmel.SAMD51_DFP.1.2.139.atpack
cd ..

curl -LO https://developer.arm.com/-/media/Files/downloads/gnu/11.3.rel1/binrel/arm-gnu-toolchain-11.3.rel1-darwin-x86_64-arm-none-eabi.tar.xz
tar Jxf arm-gnu-toolchain-11.3.rel1-darwin-x86_64-arm-none-eabi.tar.xz
cd arm-gnu-toolchain-11.3.rel1-darwin-x86_64-arm-none-eabi
find . -perm +111 -type f | while read k; do cat $k > .tmp && chmod +x .tmp && mv .tmp $k; done
cd ..

git clone --depth 1 https://github.com/shumatech/BOSSA
cd BOSSA
make bossac 2> >(grep -v found)
cd ..
