/***
*   Author: Stasiek Fortoński
*   Date: 13.08.17
*   Loaded Mission System
*   Version: 1
***/

#ifndef MISSION_HPP
#define MISSION_HPP 1
#include "loadedmission/loadedmission.hpp"
#include "../inventory/controllers/controllers.hpp"

class Mission: public LoadedMission
{
public:
    using LoadedMission::LoadedMission;

    bool isEndOfMission(const eq::Inventory & inv)
    {
        return (isAllTargetKilled() && isAllItemsInInventory(inv));
    }

    void getAwards(Stats & st, eq::Inventory & inv)
    {
        st.addExp(getAwardExp());
        st += getAwardGold();

        eq::Equipment<Item> itAward;
        for (unsigned i = 0; i < ORDERS_SIZE; ++i)
        {
            if (!getOrderedItem(i).empty())
                itAward.push_back(Item(getOrderedItem(i)));
        }
        eq::InventoryController::get().picker(inv, itAward);
    }

    void isTargetKilled(const Stats & st)
    {
        int killed = isMurderInOrder(st);
        if (killed != -1)
            getOrderedMurder(killed).second++;
        save();
    }

    operator std::string() const {return LoadedMission::getFileName();}
	std::string getInstance() const{return LoadedMission::getFileName();}

    friend std::ostream & operator<<(std::ostream & os, const Mission & m)
    {
        return os<<"Zadanie: "<<m.getNameOfMission()<<std::endl;
    }
};
#endif
