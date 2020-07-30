#pragma once

class Entity
{
public:
    bool canInteractWith(Player*);
    std::string getInteractText(Player*);
};
