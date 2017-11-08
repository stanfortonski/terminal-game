#include "npc.hpp"
#include <cmath>

struct
{
    double POWER[4];
    unsigned ENERGY[4];
} constexpr need = {
    {1.16, 1.6, 2.1, 4.1},
    {10, 30, 50, 100}
};

void NonPlayerCharacter::saveChance() const
{
    if (chance != 0)
        BasicInterpreter::save("chance", chance);
}

void NonPlayerCharacter::loadChance()
{
    BasicInterpreter::load("chance", chance);
}

void NonPlayerCharacter::load()
{
    Stats::load();
    loadChance();
}

void NonPlayerCharacter::save() const
{
    Stats::save();
    saveChance();
}

eq::Equipment<Item> NonPlayerCharacter::dropItems() const
{
    int chances = 100 - chance;
    if (chances <= 0) chances = 1;

    eq::Equipment<Item> temp;
    for (unsigned i = 0, amount = 0; i < equipment.size(); i++)
    {
        if (amount == 3) break;
        else if ((rand()%chances) == 0)
        {
            temp.push_back(equipment[i]);
            ++amount;
        }
    }
    return temp;
}

Gold NonPlayerCharacter::dropMoney() const
{
    int chances = 100 - chance;
    if (chances <= 0) chances = 1;

    if ((rand() % chances) == 0)
        return Gold(*this);
    return Gold();
}

double NonPlayerCharacter::combat()
{
    unsigned way = rand() % 6;
    for (unsigned i = 0; i < 4; ++i)
    {
        if (way == i)
        {
            if (getEnergy() >= need.ENERGY[i])
            {
                return round(getFullDamage() * need.POWER[i]);
            }
            else
            {
                --way;
                i -= 2;
                continue;
            }
        }
    }
    return getFullDamage();
}