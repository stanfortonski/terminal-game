#include "crafting.hpp"

bool eq::Crafting::whatIsMissing(Inventory & inv, const Item & it)
{
    Array arr = it.getBuildingComponents();

    bool canCreate = true;
    for (unsigned i = 1; i < arr.max_size(); ++i)
    {
        if (arr[i].empty()) continue;
        else if (inv.find(arr[i]) == -1)
        {
            std::cout<<Color::FG_RED<<"Brak składnika: "<<Color::DEFAULT<<Item(arr[i])<<std::endl;
            canCreate = false;
        }
    }
    return canCreate == true;
}

void eq::Crafting::craft(Inventory & inv, const Item & it)
{
    Array arr = it.getBuildingComponents();

    for (unsigned i = 1; i < arr.max_size(); ++i)
    {
        if (arr[i].empty()) continue;
        inv.items.pop_back(inv.find(arr[i]));
    }
    inv.add(it);
}
