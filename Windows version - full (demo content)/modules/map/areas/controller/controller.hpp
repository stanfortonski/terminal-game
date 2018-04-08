/***
* Author: Stasiek Fortoński
* Date: 30.07.2017
* Controlers of Proxy for Area
* Version: 1
***/

#ifndef PROXY_AREA_CONTROLLER_HPP
#define PROXY_AREA_CONTROLLER_HPP 1
#include "../proxy_area/proxy_area.hpp"
#include "../../../group/group.hpp"
#include "../../../fight/fight.hpp"

namespace _map
{
    class MapController
    {
    protected:
        MapController(){}
    public:
        static MapController & get()
        {
            static MapController instance;
            return instance;
        }

        int control(ProxyArea & place, Group & grp);
        int chooseNextMap(ProxyArea & place);
    };

    class CityController
    {
        int chooseNextMap(ProxyArea & place);
        int chooseNpc(ProxyArea & place, Group & grp);
        void menuInteraction(Group & grp, NonPlayerCharacter & npc);
        void setDialogueInteraction(Group & grp, NonPlayerCharacter & npc);

    protected:
        CityController(){}
    public:
        static CityController & get()
        {
            static CityController instance;
            return instance;
        }

        int control(ProxyArea & place, Group & grp);
    };

    class FieldController
    {
        int chooseNextMap(ProxyArea & place);
        int chooseNpc(ProxyArea & place, Group & my_grp);
        Group makeRandomEnemies(const ProxyArea & place) const;
        void fight_awards(Player & plr, Group & grp);

    protected:
        FieldController(){}
    public:
        static FieldController & get()
        {
            static FieldController instance;
            return instance;
        }

        int control(ProxyArea & place, Group & grp);
        void setInteraction(Group & my_grp, Group & grp);
    };
}
#endif