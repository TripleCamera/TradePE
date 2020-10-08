#pragma once

class Player
{
    // TradePE
public:
    virtual void openTradeScreen(Villager*);
};

class LocalPlayer : public Player
{
public:
    Minecraft *getMinecraft()
    { return (Minecraft*)((char*)this + 0xE38); }

    // TradePE
public:
    virtual void openTradeScreen(Villager*);
};

