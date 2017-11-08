#include "loadedmission.hpp"

using namespace std;

void LoadedMission::save() const
{
    ofstream file(BasicMission::getFileName());
    file<<"";
    file.clear();
    file.close();

    BasicMission::setNameOfMission(name);
    BasicMission::setWhoGives(who);
    BasicMission::setOrderedMurders(ordersForMurder);
    BasicMission::setOrderedItems(orderedItems);
    BasicMission::setAwardGold(gold);
    BasicMission::setAwardItems(itemInstances);
    BasicMission::setAwardExp(exp);

    for (unsigned i = 0; i < ORDERS_SIZE; ++i)
    {
        if (killed[i] != 0)
            BasicInterpreter::save("killed["+to_string(i+1)+"]", killed[i]);
    }
}

void LoadedMission::load()
{
    name = BasicMission::getNameOfMission();
    who =  BasicMission::getWhoGives();
    ordersForMurder = BasicMission::getOrderedMurders();
    orderedItems = BasicMission::getOrderedItems();
    gold = BasicMission::getAwardGold();
    itemInstances = BasicMission::getAwardItems();
    exp = BasicMission::getAwardExp();

    for (unsigned i = 0; i < ORDERS_SIZE; ++i)
    {
        unsigned temp = 0;
        BasicInterpreter::load("killed["+to_string(i+1)+"]", temp);
        killed[i] = temp;
    }
}

int LoadedMission::isMurderInOrder(const Stats & st) const
{
    for (unsigned i = 0; i < ORDERS_SIZE; ++i)
    {
        if (st.getInstance() == ordersForMurder[i].first)
            return i;
    }
    return -1;
}

bool LoadedMission::isAnItemInOrder(const string & instance) const
{
    for (unsigned i = 0; i < ORDERS_SIZE; ++i)
    {
        if (instance == orderedItems[i])
            return true;
    }
    return false;
}

bool LoadedMission::isAllTargetKilled() const
{
    for (unsigned i = 0; i < ORDERS_SIZE; ++i)
    {
        if (ordersForMurder[i].first.empty()) continue;

        if (killed[i] < ordersForMurder[i].second)
            return false;
    }
    return true;
}

bool LoadedMission::isAllItemsInInventory(const eq::Inventory & inv) const
{
	vector<unsigned> in_eq_pos;
	
    for (unsigned i = 0; i < ORDERS_SIZE; ++i)
    {
        if (!orderedItems[i].empty())
        {
			int found = inv.findWithOut(orderedItems[i], in_eq_pos);
            if (found == -1)
                return false;
			else in_eq_pos.push_back(found);
        }
    }
    return true;
}

unsigned LoadedMission::getAmountOfKills(const Stats & st) const
{
    unsigned amount = 0;
    for (unsigned i = 0; i < ORDERS_SIZE; ++i)
    {
        if (st.getInstance() == ordersForMurder[i].first)
            amount = killed[i];
    }
    return amount;
}

bool LoadedMission::isTargetKilled(const Stats & st)
{
	int order = isMurderInOrder(st);
	if (order != -1)
	{
		++killed[order];
		save();
		return true;
	}
	return false;
}