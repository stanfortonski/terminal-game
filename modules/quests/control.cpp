#include "quests.hpp"
#include "../libs/sets_types/sets_types.hpp"
#include "../libs/screen/screen.hpp"

using namespace std;
using namespace screen;

int Quests::ChooseMission() const
{
    for (;;)
    {
        clear();
        show();
        cout<<"Wybierz misje (q - powrót): ";
        string choose = setString();

        if (choose == "q") return -1;

        unsigned n = atoi(choose.c_str());
        if (n > missions.size()) continue;

        return n-1;
    }
}

void Quests::ChooseInteraction(const unsigned & numberOfMission)
{
    for (;;)
    {
        clear();
        cout<<missions[numberOfMission];

        cout<<"1. Sprawadź szczegóły misji\n";
        cout<<"2. Zrezygnuj z zadania\n";
        cout<<"3. Wróc\n";
        cout<<"Wybierz działanie: ";

        switch (setNumber<unsigned>())
        {
        case 1:
            clear();
            missions[numberOfMission].showNeeds();
            cout<<endl;
            cout<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Powrót]"<<Color::DEFAULT;
			paused();
            break;

        case 2:
            clear();
            missions.pop_back(numberOfMission);
            cout<<"Zrezygnowałeś z zadania!\n\n";
            cout<<Color::BG_BLUE<<Color::FG_YELLOW<<"[OK]"<<Color::DEFAULT;
            missions.save();
			paused();
            return;

        case 3:
        return;
        }

    }
}

void Quests::control()
{
    clear();
    if (missions.size() > 0)
    {
        int ch = ChooseMission();
        if (ch < 0) return;
        ChooseInteraction(ch);
    }
    else
    {
        cout<<"Obecnie masz brak zadań do wykonania.\n\n";
        cout<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Powrót]"<<Color::DEFAULT;
        paused();
    }
}

void Quests::endMission(Stats & me, const Stats & you)
{
    if (missions.size() > 0)
    {
        for (;;)
        {
            clear();
            unsigned num = 0;
            for (unsigned i = 0; i < ORDERS_SIZE; ++i)
            {
                if (you.getName() == missions[i].getWhoGives())
                {
                    cout<<++num<<". "<<missions[i]<<endl;
                }
            }

            if (num > 0)
            {
                cout<<"\nWybierz misje którą chcesz zakończyć (q - powrót): ";
                string ch = setString();
                if (ch == "q") return;

                unsigned choice = atoi(ch.c_str())-1;
                if (choice > num) continue;

                endMission(me, choice);
            }
            else if (num < 0)
            {
                clear();
                cout<<"Brak zadań od tej postaci.\n\n";
                cout<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Powrót]"<<Color::DEFAULT;
                paused();
            }
            return;
        }
    }
    else
    {
        clear();
        cout<<"Masz brak zadań od wykonia.\n\n";
        cout<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Powrót]"<<Color::DEFAULT;
        paused();
        return;
    }
}

void Quests::endMission(Stats & st, const unsigned & numberOfMission)
{
    clear();
    if (missions[numberOfMission].isEndOfMission(*inventory))
    {
        missions[numberOfMission].showAwards();
        cout<<endl;
        cout<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Dalej]"<<Color::DEFAULT;
        paused();
        missions[numberOfMission].getAwards(st, *inventory);
        missions.pop_back(numberOfMission);

        cout<<"\nZakończyłeś zadanie pomyślnie!\n\n";
        cout<<Color::BG_BLUE<<Color::FG_YELLOW<<"[OK]"<<Color::DEFAULT;
        missions.save();
    }
    else
    {
        cout<<Color::FG_RED<<"Nie możesz zakończyć tej misji ponieważ niespełniasz jej wymagań!\n\n"<<Color::DEFAULT;
        cout<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Powrót]"<<Color::DEFAULT;
    }
    paused();
}
