/***
* Author: Stasiek Fortoński
* Date: 09.06.2017
* Playable Class Character, save is useful with pointer Player *
* Version: 1.5
***/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_ 1
#include "../../stats/stats.hpp"
#include "../../inventory/inventory.hpp"
#include "../../crafting/crafting.hpp"
#include "../../skills/skills.hpp"
#include "../../dialogue/talkplayer.hpp"
#include "../../quests/quests.hpp"

class Player: public Stats, public TalkPlayer, private Skills, private Quests
{
private:
    eq::Inventory inventory;

    void showCombat() const;
public:
    Player(){}
    explicit Player(const std::string & fn)
    : Stats(PLAYER_DIR, fn), Skills((Stats &)*this), inventory((Stats &)*this), TalkPlayer((Stats &)*this), Quests((Stats &)*this, inventory)
    {
        Skills::load();
        inventory.load(*this);
        Quests::load(*this);
    }
    Player(const std::string & name, const int & lvl)
    : Stats(PLAYER_DIR, name, name, lvl), Skills((Stats &)*this), inventory((Stats &)*this), TalkPlayer((Stats &)*this), Quests((Stats &)*this, inventory)
    {
		onStats(Stats("players\\template"));
        Stats::save();
        Skills::contolerTreeChoser();
        Skills::save();
        inventory.save();
        Quests::save();
    }
    virtual ~Player()
    {
        save();
    }

    //cast bugfix
    operator Stats*(){return (Stats*) this;}
    operator Stats &(){return (Stats &) *this;}
    operator const Stats*(){return (const Stats*) this;}
    operator const Stats &(){return (const Stats &) *this;}

    virtual void save();
    virtual void load();

    void characterControler();
    virtual double combat();
    void pickItems(const eq::Equipment<Item> & eq);
    void goTo(const int & place){getPosition() = place;}

    virtual void show() const;

    using Quests::endMission;
    using Quests::addMission;
    using Quests::isTargetKilled;

    eq::Inventory & getInventory(){return inventory;}
    eq::Inventory getInventory() const{return inventory;}
};
#endif