#include "controller.hpp"
#include "../../../dialogue/dialogue.hpp"
#include "../../../trade/trade.hpp"

using namespace std;
using namespace screen;

int _map::CityController::control(ProxyArea & place, Group & grp)
{
    int choose = chooseNextMap(place);
    if (choose != -1) return choose;

    for (;;)
    {
        clear();
        place.show();

        cout<<"1. Twoja Postać\n";
        cout<<"2. Twoja Drużyna\n";
        cout<<"3. Postacie\n";
        cout<<"4. Droga\n";
        cout<<"5. Wyjście\n";
        cout<<"Wybierz dzialanie: ";

        switch (setNumber<unsigned>())
        {
            case 1:
                grp.player_cast(grp[0])->characterControler();
            break;

            case 2:
                grp.controlOurTeam();
            break;

            case 3:
                chooseNpc(place, grp);
            break;

            case 4:
            {
                int choose = chooseNextMap(place);
                if (choose == -1) break;
                else return choose;
            }

            case 5:
                return -1;
        }
    }
}

int _map::CityController::chooseNextMap(ProxyArea & place)
{
    return MapController::get().chooseNextMap(place);
}

int _map::CityController::chooseNpc(ProxyArea & place, Group & grp)
{
    if (place.getInstanceOfNpcs().size() > 0)
    {
        for (;;)
        {
            clear();
            place.viewNpcNames();
            cout<<"\nWybierz postać do interakcji (q - powrót): ";

            string str = setString();
            if (str == "q") break;

            unsigned choose = atoi(str.c_str())-1;
            if (choose >= place.getInstanceOfNpcs().size()) continue;

            NonPlayerCharacter npc(place.getInstanceOfNpcs()[choose]);
            menuInteraction(grp, npc);
        }
    }
    else
    {
        clear();
        cout<<Color::FG_RED<<"Brak postaci.\n\n"<<Color::DEFAULT;
        cout<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Powrót]"<<Color::DEFAULT;
        paused();
        return -1;
    }
    return 0;
}

void _map::CityController::menuInteraction(Group & grp, NonPlayerCharacter & npc)
{
    for (;;)
    {
        Player & plr = *grp.player_cast(grp[0]);
        clear();
        cout<<"Postać: "<<npc.getName()<<endl;
        cout<<"1. Rozmawiaj\n";
        cout<<"2. Zadania\n";
        cout<<"3. Wróć\n";
        cout<<"Wybierz działanie: ";

        switch (setNumber<unsigned>())
        {
            case 1:
                setDialogueInteraction(grp, npc);
            break;

            case 2:
                plr.endMission(plr, npc);
            break;

            case 3: return;
        }
    }
}

void _map::CityController::setDialogueInteraction(Group & grp, NonPlayerCharacter & npc)
{
    clear();
    Dialogue dialog(grp, 0, npc);

	if (!dialog.talk())
    {
        cout<<npc.getName()<<" cie atakuje!\n\n";
        cout<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Dalej]"<<Color::DEFAULT;
        paused();

        Group enemies;
        enemies.push_back(new NonPlayerCharacter(npc));
        FieldController::get().setInteraction(grp, enemies);
    }
    else
    {
        cout<<endl<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Zakończ rozmowe]"<<Color::DEFAULT;
        paused();
    }
}
