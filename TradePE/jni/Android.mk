LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := tradepe
LOCAL_SRC_FILES_RAW := $(shell find $(LOCAL_PATH) -name '*.cpp')  \
                       $(shell find $(LOCAL_PATH) -name '*.c')
LOCAL_SRC_FILES := $(LOCAL_SRC_FILES_RAW:$(LOCAL_PATH)/%=%)
LOCAL_LDFLAGS := -L$(LOCAL_PATH)/$(TARGET_ARCH_ABI)  \
                 -llog -ldl -lsubstrate -lminecraftpe

include $(BUILD_SHARED_LIBRARY)
