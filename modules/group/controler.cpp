#include "group.hpp"
#include "../libs/screen/screen.hpp"
#include "../libs/sets_types/sets_types.hpp"

using namespace std;
using namespace screen;

unsigned Group::playerTargetContoler(const Group & grp)
{
  for (;;)
  {
    screen::clear();
    grp.show();

    cout<<"\nWybierz cel ataku: ";
    unsigned choice = setNumber<unsigned>()-1;

    if (choice < 0 || choice >= grp.size()) continue;
    else if (grp[choice]->isDead()) continue;

    return choice;
  }
}

void Group::controlOurTeam()
{
    for (;;)
    {
        clear();
        show();

        cout<<"\nWybierz członka drużyny (q - powrót): ";
        string option = setString();
        if (option == "q") break;

        unsigned choice = atoi(option.c_str())-1;

        if (choice == 0)
        {
            clear();
            cout<<Color::FG_RED<<"Nie możesz wybrać samego siebie!"<<Color::DEFAULT<<"\n\n";
            cout<<Color::BG_BLUE<<Color::FG_YELLOW<<"[OK]"<<Color::DEFAULT;
            paused();
            continue;
        }
        else if (choice >= amount) continue;

        controlMember(choice);
    }
}

void Group::controlMember(const unsigned & choiced)
{
    for (;;)
    {
        clear();
        cout<<"Wybrałeś "<<mate[choiced]->getName()<<endl;
        cout<<"1. Zobacz szczegółowe statystyki\n";
        cout<<"2. Wyrzuć z drużyny\n";
        cout<<"3. Powrót\n\n";
        cout<<"Wybierz działanie: ";

        switch (setNumber<unsigned>())
        {
            case 1:
                clear();
                mate[choiced]->show();
                cout<<endl<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Powrót]"<<Color::DEFAULT;
                paused();
            break;

            case 2:
                pop_back(choiced);
            return;

            case 3:
                return;
        }
    }
}

void Group::addControl(Stats * st)
{
    clear();
    if (st->getLevel() < mate[0]->getLevel())
    {
        for (unsigned i = 1; i < MAXSIZE; ++i)
        {
            if (mate[i]->getInstance() == st->getInstance())
            {
                cout<<"Już jesteście w drużynie!\n\n";
                cout<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Powrót]"<<Color::DEFAULT;
                paused();
                return;
            }
        }

        for (;;)
        {
            showAdd(st);
            cout<<"Wybierz dzialanie: ";

            switch (setNumber<unsigned>())
            {
                case 1: push_back(st);
                return;
                case 2: return;
            }
        }
    }
    else
    {
        cout<<"Masz za niski poziom by dodać tą postać do drużyny!\n\n";
        cout<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Powrót]"<<Color::DEFAULT;
        paused();
    }
}
