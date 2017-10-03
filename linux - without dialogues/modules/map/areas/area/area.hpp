/***
* Author: Stasiek Fortoński
* Date: 30.07.2017
* Area System
* Version: 1
***/

#ifndef AREA_HPP
#define AREA_HPP 1
#include <iostream>
#include <vector>
#include "../../../characters/player/player.hpp"
#include "../../../characters/npc/npc.hpp"
#include "../../../libs/sets_types/sets_types.hpp"
#include "../../../libs/screen/screen.hpp"

namespace _map
{
    class Place
    {
    public:
        virtual void enter(Player & plr){}
        virtual bool canEnter(Player & plr){return true;}
        virtual void show() const{}
        virtual int type(){return -1;}

        friend ostream & operator<<(ostream & os, const Place & pl)
        {
            pl.show();
            return os;
        }
    };

    class Area: public Place, private BasicInterpreter
    {
    public:
        enum{CITY, FIELD};
    private:
        static const unsigned MAX_PLACES = 20;
        unsigned id = 0;
        Area * places[MAX_PLACES]{};
        unsigned amount = 0;

    public:
        Area(){}
        explicit Area(const std::string & fn): BasicInterpreter("maps/"+fn){id = getId();}
        virtual ~Area(){}

        virtual void enter(Player & plr){plr.goTo(id);}
        virtual bool canEnter(Player & plr){return plr.getLevel() >= getMinimalLVL();}
        void setWay(Area & ptr);
        Area & getPlace(const int & n) const;

        unsigned getId() const;
        std::string getName() const;
        std::string getDescription() const;
        std::vector<std::string> getInstanceOfNpcs() const;
        unsigned getMinimalLVL() const;
        unsigned amountOfWays() const{return amount;}
        using BasicInterpreter::getFileName;
    };

    class City: public Area
    {
    public:
        using Area::Area;
        virtual int type(){return Area::CITY;}
    };

    class Field: public Area
    {
    public:
        using Area::Area;
        virtual int type(){return Area::FIELD;}
    };
}
#endif
