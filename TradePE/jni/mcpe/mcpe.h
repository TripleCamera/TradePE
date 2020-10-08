#pragma once

#include <jni.h>
#include <dlfcn.h>
#include <sys/mman.h>
#include <android/log.h>
#include <string>
#include "Substrate.h"

#define LOG_TAG "TradePE"
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))

class Entity;
class LocalPlayer;
class Minecraft;
class Player;
class Screen;
class ScreenChooser;
class Villager;

#include "Entity.h"
    // Villager
#include "Minecraft.h"
#include "Player.h"
    // LocalPlayer
#include "Screen.h"
#include "ScreenChooser.h"
