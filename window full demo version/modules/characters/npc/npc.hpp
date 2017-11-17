/***
* Author: Stasiek Fortoński
* Date: 09.06.2017
* NonPlayable Class Character
* Version: 1.3.1
***/

#ifndef NONPLAYERCHARCTER_HPP_
#define NONPLAYERCHARCTER_HPP_ 1
#include "../../item/item.hpp"
#include "../../inventory/inventory.hpp"

class NonPlayerCharacter: public Stats
{
    unsigned chance = 2;
    eq::Equipment<Item> equipment;

    void saveChance() const;
    void loadChance();

public:
    explicit NonPlayerCharacter(const string & fn): Stats(NPC_DIR, fn), equipment(NPC_DIR+fn+"\\"+fn+"_eq")
    {
        loadChance();
        equipment.load();
    }
    NonPlayerCharacter(const string & name, const int & lvl): Stats(NPC_DIR, name, name, lvl), equipment(getInstance()+"_eq")
    {
        saveChance();
        equipment.save();
    }
    virtual ~NonPlayerCharacter(){}

    virtual void load();
    virtual void save() const;

    eq::Equipment<Item> dropItems() const;
    Gold dropMoney() const;
    double dropExp() const{return getExp();}

    virtual void show() const;
    void showPosibleAward() const;

    virtual double combat();

    unsigned getChance() const{return chance;}
    unsigned & getChance(){return chance;}

    eq::Equipment<Item> & getInventory(){return equipment;}
    eq::Equipment<Item> getInventory() const{return equipment;}
};
#endif