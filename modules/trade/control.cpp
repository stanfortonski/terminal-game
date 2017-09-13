#include "trade.hpp"
#include "../libs/sets_types/sets_types.hpp"
#include "../libs/screen/screen.hpp"

using namespace std;
using namespace screen;

void Trade::control(eq::Inventory & playerInventory, Stats & st, eq::Equipment<Item> & botInventory)
{
    for (;;)
    {
        clear();
        cout<<"1. Zobacz oferte\n";
        cout<<"2. Wysuń oferte\n";
        cout<<"3. Wróć\n";
        cout<<"Wybierz działanie: ";
        switch (setNumber<unsigned>())
        {
            case 1:
            {
                int choose = chooseItems(botInventory);
                if (choose >= 0)
                    buyDialogMenu(playerInventory, st, botInventory, choose);
                else if (choose == -1)
                {
                    cout<<"Brak oferty.";
                    cout<<endl<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Powrót]"<<Color::DEFAULT;
                    paused();
                }
            }
            break;

            case 2:
            {
                int choose = chooseItems(playerInventory.items);
                if (choose >= 0)
                    sellDialogMenu(playerInventory, st, botInventory, choose);
                else if (choose == -1)
                {
                    cout<<"Nie posiadasz przedmiotów.";
                    cout<<endl<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Powrót]"<<Color::DEFAULT;
                    paused();
                }
            }
            break;

            case 3: return;
        }
    }
}

int Trade::chooseItems(const eq::Equipment<Item> & inv)
{
    if (inv.size() > 0)
    {
        for (;;)
        {
            clear();
            inv.show();
            cout<<"Wybierz przedmiot: (q - powrót): ";
            string ch = setString();
            if (ch == "q") return -2;
            unsigned choice = atoi(ch.c_str())-1;

            if (choice > inv.size()) continue;
            return choice;
        }
    }
    return -1;
}

void Trade::buyDialogMenu(eq::Inventory & playerInventory, Stats & st, eq::Equipment<Item> & botInventory, const unsigned & num)
{
    for (;;)
    {
        clear();
        cout<<"Przedmiot: "<<botInventory[num]<<endl;
        cout<<"Wartość przedmiotu: ";
        botInventory[num].goldView();
        cout<<"\nTwoje fundusze: ";
        st.goldView();
        cout<<"\n\n1. Sprawdź informacje o przedmiocie\n";
        cout<<"2. Kup\n";
        cout<<"3. Wróć\n";

        switch (setNumber<unsigned>())
        {
            case 1:
                clear();
                botInventory[num].show();
                cout<<endl<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Powrót]"<<Color::DEFAULT;
                paused();
            break;

            case 2:
                buy(playerInventory, st, botInventory, botInventory[num]);
            return;

            case 3: return;
        }
    }
}

void Trade::sellDialogMenu(eq::Inventory & playerInventory, Stats & st, eq::Equipment<Item> & botInventory, const unsigned & num)
{
    for (;;)
    {
        clear();
        cout<<"Przedmiot: "<<playerInventory.items[num]<<endl;
        cout<<"Wartość przedmiotu: ";
        botInventory[num].goldView();
        cout<<"\nTwoje fundusze: ";
        st.goldView();
        cout<<"\n\n1. Sprawdź informacje o przedmiocie\n";
        cout<<"2. Sprzedaj\n";
        cout<<"3. Wróć\n";

        switch (setNumber<unsigned>())
        {
            case 1:
                clear();
                playerInventory.items[num].show();
                cout<<endl<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Powrót]"<<Color::DEFAULT;
                paused();
            break;

            case 2:
                //sell(playerInventory, botInventory, st, playerInventory.items[num]);
            return;

            case 3: return;
        }
    }
}
