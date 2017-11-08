#include "trade.hpp"
#include "../libs/screen/screen.hpp"

using namespace std;
using namespace screen;

void Trade::sell(eq::Inventory & playerInventory, Stats & st, eq::Equipment<Item> & botInventory, const unsigned & index)
{
	Item it = playerInventory.items[index];
	
    st.getGold() += it.getGold();
    playerInventory.items.pop_back(index);
    botInventory.push_back(it);
}

int Trade::buy(eq::Inventory & playerInventory, Stats & st, eq::Equipment<Item> & botInventory, const unsigned & index)
{
	Item it = botInventory[index];
	
    if (playerInventory.items.size() <= playerInventory.items.max_size())
    {
        if (st.enough(it))
        {
            st.getGold() -= it.getGold();
            playerInventory.items.push_back(it);
			return 1;
        }
        return 0;  
    }
    return -1;
}