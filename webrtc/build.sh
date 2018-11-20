#!/bin/sh
cd jni && ndk-build
cd ../
ant -f webrtc/webrtc/modules/build.xml
