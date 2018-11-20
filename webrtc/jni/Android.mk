#JNI_PATH := $(call my-dir)
JNI_PATH := ../
subdirs += $(JNI_PATH)/Android.mk
#include $(call all-subdir-makefiles)
include $(subdirs)


