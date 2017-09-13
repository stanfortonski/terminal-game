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
        if (must_kill[i] != 0)
            BasicInterpreter::save("must_kill["+to_string(i+1)+"]", must_kill[i]);
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
        BasicInterpreter::load("must_kill["+to_string(i+1)+"]", temp);
        must_kill[i] = temp;
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

        if (ordersForMurder[i].second < must_kill[i])
            return false;
    }
    return true;
}

bool LoadedMission::isAllItemsInInventory(const eq::Inventory & inv) const
{
    for (unsigned i = 0; i < ORDERS_SIZE; ++i)
    {
        if (!orderedItems[i].empty())
        {
            if (inv.find(orderedItems[i]) == -1)
                return false;
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
            amount = ordersForMurder[i].second;
    }
    return amount;
}
