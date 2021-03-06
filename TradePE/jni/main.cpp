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

#include "mcpe/mcpe.h"


static bool Villager_canInteractWith(Villager *self, Player *p)
{ return !(self -> isTrading()); }

static std::string Villager_getInteractText(Villager*, Player*)
{ return "Trade"; }

static void Villager_interactWithPlayer(Villager *v, Player *p)
{
    if ( !(Villager_canInteractWith(v,p)) )
    {
        LOGI("Fail");
        return;
    }
    LOGI("Interact");
    // ???
    //p -> openTradeScreen(v);
}

void vtable_hook(void **vtable, void *symbol, void *hook)
{
    void **addr = vtable;
    while ((*addr) != symbol)
        addr++;
    int pagesize = getpagesize();
    void *page = (void*)((unsigned int)addr / pagesize * pagesize);
    LOGI("Vtable hook: addr = 0x%x", (unsigned int)addr);

    int result = mprotect(page, pagesize, PROT_READ | PROT_WRITE);
    if (result == 0)
        LOGI("mprotect(0x%x) succeeded", (unsigned int)page);
    else
        LOGI("mprotect(0x%x) failed, errno %d\n", (unsigned int)page, errno);
    *addr = hook;
    mprotect(page, pagesize, PROT_READ | PROT_EXEC);
}

JNIEXPORT jint JNI_OnLoad(JavaVM*, void*)
{
    void *handle = dlopen("libminecraftpe.so", RTLD_LAZY);
    void *vtable_Villager = dlsym(handle, "_ZTV8Villager");
    vtable_hook( (void**) vtable_Villager,
                 (void* ) &Entity::canInteractWith,
                 (void* ) &Villager_canInteractWith );
    vtable_hook( (void**) vtable_Villager,
                 (void* ) &Entity::getInteractText,
                 (void* ) &Villager_getInteractText );
    vtable_hook( (void**) vtable_Villager,
                 (void* ) &Villager::interactWithPlayer,
                 (void* ) &Villager_interactWithPlayer );
    dlclose(handle);
    return JNI_VERSION_1_6;
}
