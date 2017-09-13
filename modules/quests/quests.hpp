/***
*   Author: Stasiek Fortoński
*   Date: 13.08.17
*   Quetsts
*   Version: 1.1
***/

#ifndef QUESTS_HPP
#define QUESTS_HPP 1
#include <iostream>
#include <cstdlib>
#include "../mission/mission.hpp"

class Quests
{
    eq::Equipment<Mission> missions;
    eq::Inventory * inventory = nullptr;

    int ChooseMission() const;
    void ChooseInteraction(const unsigned & numberOfMission);

public:
    Quests(){}
    Quests(Stats & st, eq::Inventory & inv): inventory(&inv)
    {
        if (system(string("mkdir -p "+PLAYER_DIR+st.getName()+"/missions").c_str()) != -1);
        missions.getFileName() = st.getInstance()+"_quests";
    }

    void load(Stats & st);
    void save() const;
    void show() const{missions.show();}

    void isTargetKilled(const Stats & st);
    void control();

    void addMission(const BasicMission & bs, Stats & st, const std::string & who);
    void endMission(Stats & me, const Stats & you);
    void endMission(Stats & st, const unsigned & numberOfMission);

    Mission & getMission(const unsigned & n){return missions[n];}
    Mission getMission(const unsigned & n) const{return missions[n];}
};
#endif
