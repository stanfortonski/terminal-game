#include "controller.hpp"
#include <utility>

using namespace std;
using namespace screen;

int _map::FieldController::control(ProxyArea & place, Group & grp)
{
    int choose = chooseNextMap(place);
    if (choose != -1) return choose;

    for (;;)
    {
        clear();
        place.show();

        cout<<"1. Twoja Postać\n";
        cout<<"2. Twoja Drużyna\n";
        cout<<"3. Przeciwnicy\n";
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
                if (chooseNpc(place, grp) == -1)
                {
                    clear();
                    cout<<Color::FG_RED<<"Brak przeciwników.\n\n"<<Color::DEFAULT;
                    cout<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Powrót]"<<Color::DEFAULT;
                    paused();
                }
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

int _map::FieldController::chooseNextMap(ProxyArea & place)
{
    return MapController::get().chooseNextMap(place);
}

Group _map::FieldController::makeRandomEnemies(const ProxyArea & place) const
{
    Group grp;

    vector<string> inst = place.getInstanceOfNpcs();
    random_shuffle(inst.begin(), inst.end());

    unsigned max = rand()%6+1;
    if (max > inst.size()) max = inst.size();

    for (unsigned i = 0; i < max; ++i)
        grp.push_back(new NonPlayerCharacter(inst[i]));

    return grp;
}

int _map::FieldController::chooseNpc(ProxyArea & place, Group & my_grp)
{
    if (place.getInstanceOfNpcs().size() > 0)
    {
        clear();
        unsigned randomize = rand()%5;
        if (randomize == 0) return -1;

        Group grps[randomize];

        for (unsigned i = 0; i < randomize; ++i)
            grps[i] = makeRandomEnemies(place);

        for (;;)
        {
            clear();
            for (unsigned i = 0; i < randomize; ++i)
            {
                cout<<"Grupa "<<i+1<<endl;
                grps[i].show();
                cout<<endl;
            }

            cout<<"Wybierz przeciwników (q - powrót): ";

            string ch = setString();
            if (ch == "q") return -2;
            unsigned choice = atoi(ch.c_str())-1;

            if (choice >= randomize)
                continue;

            setInteraction(my_grp, grps[choice]);
            return 0;
        }
    }
    return -1;
}

void _map::FieldController::setInteraction(Group & my_grp, Group & enemies)
{
    for (;;)
    {
        clear();
        cout<<"1. Zaatakuj\n";
        cout<<"2. Uciekaj\n\n";
        cout<<"Wybierz działanie: ";

        unsigned ch = setNumber<unsigned>();
        if (ch == 1)
        {
            if (Fight::get().groupVersusGroup(my_grp, enemies) == 1)
            {
                fight_awards(*my_grp.player_cast(my_grp[0]), enemies);
            }
            else
            {
                clear();
                cout<<"Przegrałeś potyczkę!\n\n";
                cout<<"Udało ci się uciec... Idź czym prędzej się uleczyć!\n\n";
                cout<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Dalej]"<<Color::DEFAULT;
                paused();
            }
            break;
        }
        else if (ch == 2) break;
        else continue;
    }
}

void _map::FieldController::fight_awards(Player & plr, Group & grp)
{
    unsigned exps = 0;
    int gold = 0;
    eq::Equipment<Item> items;

    for (unsigned i = 0; i < grp.size(); ++i)
    {
        NonPlayerCharacter & npc = *grp.npc_cast(grp[i]);

        plr.isTargetKilled(npc);
        exps += npc.dropExp();
        gold += npc.dropMoney();
        items.push_back(npc.dropItems());
    }

    clear();
    cout<<"Wygrałeś potyczkę!\n\n";
    cout<<"Zdobyłeś:\n";
    if (exps > 0) cout<<" - doświadczenie +"<<exps<<endl;
    if (gold > 0) cout<<" - "<<gold<<" złota\n";

    plr.addExp(exps);
    plr += gold;

    cout<<endl<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Dalej]"<<Color::DEFAULT;
    paused();

    plr.pickItems(items);
}
