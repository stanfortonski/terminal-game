#include "basicskills.hpp"

void BasicSkills::calc()
{
    for (int i = 0; i < AMOUNT_SKILLS; ++i)
        power[i] = level[i] * power[i];
}

bool BasicSkills::upgrade(const unsigned & n)
{
    if (level[n] < MAX_LEVEL)
    {
        ++level[n];
        return true;
    }
    return false;
}

unsigned BasicSkills::energyTakes(const unsigned & n) const
{
    int temp = energyEat[n] - level[n];
    return temp < 0 ? 0 : temp;
}