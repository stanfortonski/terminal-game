#include "controller.hpp"

using namespace std;
using namespace screen;

int _map::MapController::control(ProxyArea & place, Group & grp)
{
    if (place.type() == Area::CITY)
        return CityController::get().control(place, grp);
    return FieldController::get().control(place, grp);
}

int _map::MapController::chooseNextMap(ProxyArea & place)
{
    for (;;)
    {
        clear();
        cout<<Color::FG_LIGHTBLUE<<"Znajdujesz się w: "<<place.getName()<<"\n\n"<<Color::DEFAULT;
        place.viewWays();
        cout<<"Wybierz trase (q - zostań): ";
        string pick = setString();
        if (pick == "q") return -1;

        unsigned choose = atoi(pick.c_str());
        if (choose > place.amountOfWays()) continue;
        else return choose-1;
    }
}
