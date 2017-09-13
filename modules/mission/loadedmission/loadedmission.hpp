/***
*   Author: Stasiek Fortoński
*   Date: 13.08.17
*   Loaded Mission System
*   Version: 1
***/

#ifndef LOADED_MISSION_HPP
#define LOADED_MISSION_HPP 1
#include "../basic_mission/basic_mission.hpp"

class LoadedMission: protected BasicMission
{
    std::string name;
    std::string who;
    Gold gold;
    unsigned exp = 0;
    std::array<std::pair<std::string, unsigned>, ORDERS_SIZE> ordersForMurder;
    std::array<unsigned, ORDERS_SIZE> must_kill;
    std::array<std::string, ORDERS_SIZE> orderedItems;
    std::array<std::string, ORDERS_SIZE> itemInstances;

public:
    LoadedMission(){}
    LoadedMission(const std::string & fn): BasicMission(fn)
    {
        BasicMission::getFileName().erase(0, 9);
        load();
    }

    LoadedMission(const BasicMission & quest, const Stats & st, const std::string & missionGetter): BasicMission(quest)
    {
        must_kill.fill(0);
        ordersForMurder.fill({"", 0});

        load();
        for (unsigned i = 0; i < ORDERS_SIZE; ++i)
        {
            must_kill[i] = ordersForMurder[i].second;
            ordersForMurder[i].second = 0;
        }

        BasicMission::getFileName() = PLAYER_DIR+st.getName()+"/"+BasicMission::getFileName()+"_by_"+missionGetter;
        who = missionGetter;
        save();
    }

    LoadedMission(const string & fn,
        const string & n,
        const string & w,
        const std::array<std::pair<std::string, unsigned>, ORDERS_SIZE> & ofm,
        const std::array<std::string, ORDERS_SIZE> & oi,
        const Gold & g,
        const std::array<std::string, ORDERS_SIZE> & its,
        const unsigned & e)
        : BasicMission(fn), name(n), who(w),
    ordersForMurder(ofm), orderedItems(oi), gold(g), itemInstances(its), exp(e)
    {
        save();
    }

    void save() const;
    void load();

    std::string & getNameOfMission(){return name;}
    std::string getNameOfMission() const{return name;}

    std::string & getWhoGives(){return who;}
    std::string getWhoGives() const{return who;}

    std::pair<std::string, unsigned> & getOrderedMurder(const unsigned & n){return ordersForMurder[n];}
    std::pair<std::string, unsigned> getOrderedMurder(const unsigned & n) const{return ordersForMurder[n];}

    std::string & getOrderedItem(const unsigned & n){return orderedItems[n];}
    std::string getOrderedItem(const unsigned & n) const{return orderedItems[n];}

    std::array<std::string, ORDERS_SIZE> getAwardItems() const{return itemInstances;}
    std::array<std::string, ORDERS_SIZE> & getAwardItems(){return itemInstances;}

    unsigned & getAwardExp(){return exp;}
    unsigned getAwardExp() const{return exp;}

    int isMurderInOrder(const Stats & st) const;
    bool isAnItemInOrder(const string & instance) const;
    bool isAllTargetKilled() const;
    bool isAllItemsInInventory(const eq::Inventory & inv) const;
    unsigned getAmountOfKills(const Stats & st) const;

    void showNeeds() const;
    void showAwards() const;

    std::string getFileName() const
    {
        return BasicInterpreter::getFileName();
    }
};
#endif
