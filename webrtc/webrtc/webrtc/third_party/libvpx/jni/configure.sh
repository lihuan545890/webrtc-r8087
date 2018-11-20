#!/bin/sh

./libvpx/configure --target=armv7-android-gcc \
		   --disable-examples \
		   --sdk-path=/project/android-ndk-r10e \
		   --extra-cflags="-mfloat-abi=softfp -mfpu=neon"

