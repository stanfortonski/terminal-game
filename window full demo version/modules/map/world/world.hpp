/***
* Author: Stasiek Fortoński
* Date: 29.07.2017
* World System
* Version: 1
***/

#ifndef WORLD_HPP
#define WORLD_HPP 1
#include "../areas/controller/controller.hpp"

namespace _map
{
    static const int WORLD_SIZE = 14;
    class World
    {
        Area * areas[WORLD_SIZE];
        ProxyArea * actual = nullptr;

        void nextMap(Player & plr, Area & place);

    protected:
        World();
        virtual ~World()
        {
            delete actual;
            for (int i = 0; i < WORLD_SIZE; ++i)
                delete areas[i];
        }

    public:
        static World & get()
        {
            static World instance;
            return instance;
        }

        void enter(Group & grp);
    };
}
#endif
