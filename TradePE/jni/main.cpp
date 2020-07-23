/**
 *  TradePE - A Native Addon for Minecraft PE
 *  Copyright (C) 2020  TripleCamera
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <jni.h>
#include <dlfcn.h>
#include <sys/mman.h>
#include <android/log.h>
#include "Substrate.h"
#include "mcpe/mcpe.h"

#define LOG_TAG "TradePE"
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))

static bool Villager_canInteract(Villager*, Player*)
{ return true; }

void vtable_hook(void** vtable, void* symbol, void* hook)
{
    void** addr = vtable;
    while ((*addr) != symbol)
        addr++;
    int pagesize = getpagesize();
    void* page = (void*)((unsigned int)addr / pagesize * pagesize);
    LOGI("Vtable hook 0x%x, mprotect page 0x%x",
         (unsigned int)vtable, (unsigned int)page);

    int result = mprotect(page, pagesize, PROT_READ | PROT_WRITE);
    if (result == 0)
        LOGI("mprotect succeeded");
    else
        LOGI("mprotect failed, errno %d\n", errno);
    *addr = hook;
    mprotect(page, pagesize, PROT_READ | PROT_EXEC);
}

JNIEXPORT jint JNI_OnLoad(JavaVM*, void*)
{
    void* handle = dlopen("libminecraftpe.so", RTLD_LAZY);
    void* vtable_Villager = dlsym(handle, "_ZTV8Villager");
    vtable_hook( (void**) vtable_Villager,
                 (void* ) &Entity::canInteractWith,
                 (void* ) &Villager_canInteract );
    dlclose(handle);
    return JNI_VERSION_1_6;
}
