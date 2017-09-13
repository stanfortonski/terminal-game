#include "group.hpp"
#include <algorithm>

bool Group::push_back(Stats * ptr)
{
    if (full()) return false;
    mate[amount++] = ptr;
    return true;
}

void Group::pop_back()
{
    if (!empty())
    {
        delete mate[--amount];
        mate[--amount] = nullptr;
    }
}

void Group::pop_back(const unsigned & n)
{
    if (mate[n] != nullptr)
    {
        for (unsigned i = n+1; i < amount; ++i)
            mate[i-1] = mate[i];

        delete mate[--amount];
        mate[amount] = nullptr;
    }
}

void Group::sort()
{
    if (!empty())
    {
        std::sort(mate, mate+amount, [](Stats * a, Stats * b){
            return !(*a < *b);
        });
    }
}

void Group::random()
{
    if (!empty())
    {
        std::random_shuffle(mate, mate+amount);
    }
}

bool Group::allIsDeath() const
{
  for (unsigned i = 0; i < amount; ++i)
  {
      if (!mate[i]->isDead())
        return false;
  }
  return true;
}

void Group::regenerations()
{
    for (unsigned i = 0; i < amount; ++i)
    {
        if (!mate[i]->isDead())
        {
            mate[i]->regenerateEnergy();
            mate[i]->regenerateHp();
        }
    }
}

unsigned Group::npcTargetControler(const Group & grp)
{
    unsigned choice = 0;
    switch (rand()%3+1)
    {
    case 1:
    case 2:
        for (unsigned i = 0; i < grp.size(); ++i)
        {
            if (grp[i]->isDead()) continue;
            else if (grp[i]->getLevel() < grp[choice]->getLevel()) choice = i;
        }
        while (grp[choice]->isDead()){
            choice = rand()%grp.size();
        }
        break;

    default:
        do{
            choice = rand()%grp.size();
        }while (grp[choice]->isDead());
    }
    return choice;
}

unsigned Group::target(const unsigned & n, const Group & grp)
{
    if (mate[n]->isDead()) return 0;

    if (player_cast(mate[n]) != nullptr)
        return playerTargetContoler(grp);
    return npcTargetControler(grp);
}
