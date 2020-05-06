#include "world.hpp"

using namespace std;
using namespace screen;

_map::World::World()
{
    areas[0] = new City("stan_place");
    areas[1] = new Field("coast");
    areas[2] = new Field("glade");
    areas[3] = new Field("cliff");
    areas[4] = new Field("small_forest");
    areas[5] = new Field("forest");
    areas[6] = new City("flawhang/port");
    areas[7] = new City("flawhang/market");
    areas[8] = new City("flawhang/west_gate");
    areas[9] = new City("flawhang/center");
    areas[10] = new City("flawhang/town_hall");
    areas[11] = new City("flawhang/tavern");
    areas[12] = new City("flawhang/church");
    areas[13] = new City("flawhang/east_gate");
    //ways
    areas[0]->setWay(*areas[1]);
    areas[1]->setWay(*areas[6]);
    areas[6]->setWay(*areas[7]);
    areas[7]->setWay(*areas[8]);
    areas[7]->setWay(*areas[9]);
    areas[8]->setWay(*areas[2]);
    areas[2]->setWay(*areas[3]);
    areas[9]->setWay(*areas[10]);
    areas[9]->setWay(*areas[11]);
    areas[9]->setWay(*areas[12]);
    areas[9]->setWay(*areas[13]);
    areas[13]->setWay(*areas[4]);
    areas[4]->setWay(*areas[5]);
}

void _map::World::nextMap(Player & plr, Area & place)
{
    delete actual;
    actual = new ProxyArea(place);
    actual->enter(plr);
}

void _map::World::enter(Group & grp)
{
    for (int i = 0; i < WORLD_SIZE; ++i)
    {
        if (areas[i]->getId() == grp.player_cast(grp[0])->getPosition())
        {
            nextMap(*grp.player_cast(grp[0]), *areas[i]);
            for (;;)
            {
                int choose = MapController::get().control(*actual, grp);
                if (choose != -1)
                {
                    Area & next = actual->getPlace(choose);
                    if (!next.canEnter(*grp.player_cast(grp[0])))
                    {
                        clear();
                        cout<<Color::RED<<"Masz za niski poziom by tam p¢j˜†!\n\n"<<Color::DEFAULT;
                        cout<<Color::YELLOW<<"[Powr¢t]"<<Color::DEFAULT;
                        paused();
                    }
                    else nextMap(*grp.player_cast(grp[0]), next);
                }
                else return;
            }
            break;
        }
    }
}