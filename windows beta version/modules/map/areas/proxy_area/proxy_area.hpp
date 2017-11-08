/***
* Author: Stasiek Fortoński
* Date: 30.07.2017
* Proxy for Area
* Version: 1
***/

#ifndef PROXY_AREA_HPP
#define PROXY_AREA_HPP 1
#include "../area/area.hpp"

namespace _map
{
    class ProxyArea: public Place
    {
        Area * here = nullptr;
        std::string name;
        std::string desc;
        unsigned minimalLVL = 0;
        std::vector<std::string> npcInstances;

    public:
        ProxyArea(Area & st): here(&st)
        {
            name = here->getName();
            desc = here->getDescription();
            minimalLVL = here->getMinimalLVL();
            npcInstances = here->getInstanceOfNpcs();
        }
        virtual ~ProxyArea(){}

        virtual void enter(Player & plr){here->enter(plr);}
        virtual bool canEnter(Player & plr){return here->canEnter(plr);}
        void setWay(Area & ptr){here->setWay(ptr);}
        virtual int type(){return here->type();}

        unsigned getId() const{return here->getId();};
        std::string getName() const{return name;}
        std::string getDescription() const{return desc;}
        std::vector<std::string> getInstanceOfNpcs() const{return npcInstances;}
        unsigned getMinimalLVL() const{return minimalLVL;}
        Area & getPlace(const int & n) const{return here->getPlace(n);}
        unsigned amountOfWays() const{return here->amountOfWays();}

        virtual void show() const;
        void viewWays() const;
        void viewNpcNames() const;
    };
}
#endif