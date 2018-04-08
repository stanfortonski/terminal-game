/***
* Author: Stasiek Fortoäski
* Date: 09.07.2017
* Terminal-game Item Maker
* Version: 2
***/

#include <iostream>
#include <string>
#include "../modules/item/item.hpp"
#include "../modules/libs/sets_types/sets_types.hpp"

using namespace std;

int main()
{
    for (;;)
    {
        screen::clear();
        string instance, name, desc;
        unsigned type, rank, need_lvl, need_str, need_dex;

        cout<<"\nTerminal-game Item Maker\n\n";

        cout<<"Podaj instancje przedmiotu: ";
        instance = setString();

        cout<<"Podaj nazwe przedmiotu: ";
        name = setString();

        cout<<endl;

        for (int i = 0; i <= 10; ++i)
            cout<<i<<".\t"<<TypeItem(TypeItem::Type(i)).getStringType()<<endl;

        cout<<"Podaj typ przedmiotu (liczbowo): ";
        type = setNumber<unsigned>();

        cout<<endl;

        for (int i = 0; i <= 8; ++i)
        {
            cout<<i<<".\t";
            if (i == 0) cout<<"brak";
            cout<<RankItem(RankItem::Rank(i)).getRankName()<<endl;
        }
        cout<<"Podaj range przedmiotu (liczbowo): ";
        rank = setNumber<unsigned>();

        cout<<"Podaj opis przedmiotu: ";
        desc = setString();

        cout<<"Podaj wymagany poziom do noszenia: ";
        need_lvl = setNumber<unsigned>();

        cout<<"Podaj wymagan¥ siˆe do noszenia: ";
        need_str = setNumber<unsigned>();

        cout<<"Podaj wymagan¥ zr©czno˜† do noszenia: ";
        need_dex = setNumber<unsigned>();

        Item it(instance, name, TypeItem::Type(type), RankItem::Rank(rank), desc, need_lvl, need_str, need_dex);

        cout<<"Podaj cene przedmiotu: ";
        it.getGold() = Gold(setNumber<int>());

        Array bufor;
        if (it.getValueType() == TypeItem::Type::RECIPE)
        {
            cout<<"Podaj instancje przedmiotu kt¢rego nauczysz si© wykona†: ";
            getline(cin, bufor[0]);
            bufor[0] = bufor[0];
            cin.clear();
        }
        else
        {
            string temp;
            cout<<"Podaj instancje potrzebnego skˆadnika by wykonac ten przedmiot (Uwaga max 10, q - nie ustawiaj skˆadnik¢w): ";
            for (unsigned i = 1; getline(cin, temp) && temp != "q" && i < bufor.max_size(); ++i)
            {
                if (!temp.empty())
                {
                    bufor[i] = temp;
                }
                else
                {
                    --i;
                    continue;
                }
                if (i+1 != bufor.max_size())
                    cout<<i+1<<". Podaj instancje potrzebnego skˆadnika (q - zakoäczy dodawanie skˆadnik¢w): ";
            }
            cin.clear();
            while (cin.get() != '\n') continue;
        }
        it.setBuildingComponents(bufor);

        cout<<"Podaj ile przywraca ¾ycia: ";
        it.getHp() = setNumber<long>();
        it.save();

        cout<<"Podaj ile dodaje maksymalnego ¾ycia: ";
    	it.getMaxHp() = setNumber<long>();
        it.save();

        cout<<"Podaj regeneracje ¾ycia: ";
    	it.getRegenerationHp() = setNumber<int>();
        it.save();

        cout<<"Podaj obrone: ";
    	it.getDef() = setNumber<double>();
        it.save();

        cout<<"Podaj ile przywraca energie (liczbowo w % np. 10): ";
        it.getEnergy() = setNumber<unsigned>();
        it.save();

        cout<<"Podaj ile dodaje energii maskymalnej: ";
        it.getMaxEnergy() = setNumber<unsigned>();
        it.save();

        cout<<"Podaj regeneracje energii: ";
        it.getRegenerationEnergy() = setNumber<int>();
        it.save();

        cout<<"Podaj szanse na unik (liczbowo w % np. 10): ";
        it.getDodge() = setNumber<int>();
        it.save();

        cout<<"Podaj szanse na blok (liczbowo w % np. 10): ";
        it.getBlock() = setNumber<int>();
        it.save();

        cout<<"Podaj szanse na konstratak (liczbowo w % np. 10): ";
        it.getHitback() = setNumber<int>();
        it.save();

        cout<<"Podaj siˆ©: ";
        it.getStr() = setNumber<double>();
        it.save();

        cout<<"Podaj obra¾enia minimalne: ";
        it.getMinDmg() = setNumber<int>();
        it.save();

        cout<<"Podaj obra¾enia maksymalne: ";
        it.getMaxDmg() = setNumber<int>();
        it.save();

        cout<<"Podaj szanse na cios krytyczny (liczbowo w % np. 10): ";
        it.getCrit() = setNumber<int>();
        it.save();

        cout<<"Podaj moc ciosu krytycznego (liczbowo w % np. 10): ";
        it.getCritStr() = setNumber<int>();
        it.save();

        cout<<"Podaj zr©czno˜†: ";
        it.getDex() = setNumber<double>();
        it.save();

        screen::clear();
        it.show();
        cout<<"Ukoäczono tworzenie przedmiotu!\n\n[Dalej]";
        screen::paused();
    }
    cout<<"Gotowe!\n";
}