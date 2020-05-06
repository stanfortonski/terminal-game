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
        cout<<"2. Wysuä oferte\n";
        cout<<"3. Wr¢†\n";
        cout<<"Wybierz dziaˆanie: ";
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
                    cout<<endl<<Color::YELLOW<<"[Powr¢t]"<<Color::DEFAULT;
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
                    cout<<"Nie posiadasz przedmiot¢w.";
                    cout<<endl<<Color::YELLOW<<"[Powr¢t]"<<Color::DEFAULT;
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
            cout<<"Wybierz przedmiot: (q - powr¢t): ";
            string ch = setString();
            if (ch == "q") return -2;
            unsigned choice = atoi(ch.c_str())-1;

            if (choice > inv.size()) continue;
            return choice;
        }
    }
    return -1;
}

void Trade::buyDialogMenu(eq::Inventory & playerInventory, Stats & st, eq::Equipment<Item> & botInventory, const unsigned & index)
{
    for (;;)
    {
        clear();
        cout<<"Przedmiot: "<<botInventory[index]<<endl;
        cout<<"Warto˜† przedmiotu: ";
        botInventory[index].goldView();
        cout<<"\nTwoje fundusze: ";
        st.goldView();
        cout<<"\n\n1. Sprawd« informacje o przedmiocie\n";
        cout<<"2. Kup\n";
        cout<<"3. Wr¢†\n";

        switch (setNumber<unsigned>())
        {
            case 1:
                clear();
                botInventory[index].show();
                cout<<endl<<Color::YELLOW<<"[Powr¢t]"<<Color::DEFAULT;
                paused();
            break;

            case 2:
			{
				int isBought = buy(playerInventory, st, botInventory, index);
				clear();
				if (isBought == 1) cout<<Color::GREEN<<"Kupiˆe˜ przedmiot!\n\n"<<Color::DEFAULT;
				else if (isBought == 0) cout<<Color::RED<<"Brak funduszy by zakupi† ten przedmiot!\n\n"<<Color::DEFAULT;
				else cout<<Color::RED<<"Brak miejsca w twoim inwentarzu!\n\n"<<Color::DEFAULT;
			   
			    cout<<Color::YELLOW<<"[OK]"<<Color::DEFAULT;
				paused();
			}
            case 3: return;
        }
    }
}

void Trade::sellDialogMenu(eq::Inventory & playerInventory, Stats & st, eq::Equipment<Item> & botInventory, const unsigned & index)
{
    for (;;)
    {
        clear();
        cout<<"Przedmiot: "<<playerInventory.items[index]<<endl;
        cout<<"Warto˜† przedmiotu: ";
        playerInventory.items[index].goldView();
        cout<<"\nTwoje fundusze: ";
        st.goldView();
        cout<<"\n\n1. Sprawd« informacje o przedmiocie\n";
        cout<<"2. Sprzedaj\n";
        cout<<"3. Wr¢†\n";

        switch (setNumber<unsigned>())
        {
            case 1:
                clear();
                playerInventory.items[index].show();
                cout<<endl<<Color::YELLOW<<"[Powr¢t]"<<Color::DEFAULT;
                paused();
            break;

            case 2:
                sell(playerInventory, st, botInventory, index);
				clear();
				cout<<Color::GREEN<<"Sprzedaˆe˜ przedmiot!\n\n"<<Color::DEFAULT;
				cout<<Color::YELLOW<<"[OK]"<<Color::DEFAULT;
				paused();
            return;

            case 3: return;
        }
    }
}