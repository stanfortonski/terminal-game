#include "trade.hpp"
#include "../libs/screen/screen.hpp"

using namespace std;
using namespace screen;

void Trade::sell(eq::Inventory & playerInventory, Stats & st, eq::Equipment<Item> & botInventory, const Item & it)
{
    int n = playerInventory.find(it.getInstance());
    if (n != -1)
    {
        st.getGold() += it.getGold();
        playerInventory.items.pop_back(n);
        botInventory.push_back(it);

        clear();
        cout<<"Sprzedałeś przedmiot!\n";
        cout<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Powrót]"<<Color::DEFAULT;
        paused();
    }
}

void Trade::buy(eq::Inventory & playerInventory, Stats & st, eq::Equipment<Item> & botInventory, const Item & it)
{
    if (playerInventory.items.size() < playerInventory.items.max_size())
    {
        if (st.enough(it))
        {
            st.getGold() -= it.getGold();
            playerInventory.items.push_back(it);

            clear();
            cout<<"Kupiłeś przedmiot!\n\n";
        }
        else
        {
            clear();
            cout<<Color::FG_RED<<"Brak funduszy by zakupić ten przedmiot!\n\n"<<Color::DEFAULT;
        }
    }
    else
    {
        clear();
        cout<<Color::FG_RED<<"Brak miejsca w twoim inwentarzu!\n\n"<<Color::DEFAULT;
    }

    cout<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Powrót]"<<Color::DEFAULT;
    paused();
}
