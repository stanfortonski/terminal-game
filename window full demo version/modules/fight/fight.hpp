/***
* Author: Stasiek Fortoński
* Date: 24.06.2017
* Fight System
* Version: 3
***/

#ifndef FIGHT_HPP_
#define FIGHT_HPP_ 1
#include <iostream>
#include <algorithm>
#include "../group/group.hpp"
#include "battle_view/battle_view.hpp"
#include "../libs/sets_types/sets_types.hpp"
#include "../libs/screen/screen.hpp"

class BasicFight
{
public:
    virtual void attack(Stats & attacker, Stats & defending) const{};
    virtual unsigned groupVersusGroup(Group & grpa, Group & grpb) const{return 0;};
};

class Fight: public BasicFight
{
    BasicBattleView * view = &BattleView::get();

    void beforeAttack(const unsigned & n_attacker, Group & attackers, Group & defenders) const;
    
protected:
    Fight(){}
public:
    static Fight & get()
    {
        static Fight instance;
        return instance;
    }

    virtual void attack(Stats & attacker, Stats & defending) const;
    virtual unsigned groupVersusGroup(Group & grpa, Group & grpb) const;
};
#endif