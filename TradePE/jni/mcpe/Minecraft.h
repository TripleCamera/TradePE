#pragma once

class Minecraft
{
public:
    ScreenChooser *getScreenChooser()
    { return (ScreenChooser*)((char*)this + 0x70); }
};
