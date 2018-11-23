#!/bin/bash

NDK=/project/android-ndk-r10e

PLATFORM=$NDK/platforms/android-19/arch-arm
TOOLCHAIN=$NDK/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64
PREFIX=../ffmpeg/libx264

function build_one
{
./configure \
--prefix=$PREFIX \
--enable-static \
--enable-pic \
--enable-strip \
--host=arm-linux-androideabi \
--cross-prefix=$TOOLCHAIN/bin/arm-linux-androideabi- \
--sysroot=$PLATFORM \
--extra-cflags="-Os -fpic" \
--extra-ldflags="-fuse-ld=bfd -Wl,--fix-cortex-a8" \

$ADDITIONAL_CONFIGURE_FLAG
make STRIP=
make install

}
build_one
