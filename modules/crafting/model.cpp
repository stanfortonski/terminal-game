#include "crafting.hpp"

bool eq::Crafting::whatIsMissing(Inventory & inv, const Item & it)
{
    Array arr = it.getBuildingComponents();
	std::vector<unsigned> pos;
	
    bool canCreate = true;
    for (unsigned i = 1; i < arr.max_size(); ++i)
    {
        if (arr[i].empty()) continue;
		
		int found = inv.findWithOut(arr[i], pos);
        if (found == -1)
        {
            std::cout<<Color::RED<<"Brak skˆadnika: "<<Color::DEFAULT<<Item(arr[i])<<std::endl;
            canCreate = false;
        }
		else pos.push_back(found); 
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