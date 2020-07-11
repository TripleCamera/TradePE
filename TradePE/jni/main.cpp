#include <jni.h>
#include <dlfcn.h>
#include <android/log.h>
#include "Substrate.h"
#include "mcpe.h"

#define LOG_TAG "TradePE"
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))

JNIEXPORT jint JNI_OnLoad(JavaVM*, void*)
{
    LOGI("Hello World! ");
    return JNI_VERSION_1_6;
}
