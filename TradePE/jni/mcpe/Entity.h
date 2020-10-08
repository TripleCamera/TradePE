#pragma once

class Entity
{
public:
    /*virtual*/ bool canInteractWith(Player*);
    /*virtual*/ std::string getInteractText(Player*);
};

class Villager
{
public:
    // DO NOT DEFINE FUNCTIONS THAT DON'T EXIST!!!
    bool isTrading(void) const;
    void interactWithPlayer(Player*);
};
