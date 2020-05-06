/***
* Author: Stasiek Fortoäski
* Date: 09.07.2017
* Terminal-game NPC Maker
* Version: 1
***/

#include <iostream>
#include <string>
#include "../modules/characters/npc/npc.hpp"
#include "../modules/libs/sets_types/sets_types.hpp"

using namespace std;

int main()
{
    for (;;)
    {
        screen::clear();
        string instance, name;
        unsigned lvl;

        cout<<"\nTerminal-game NPC Maker\n\n";

        cout<<"Podaj instancje: ";
        instance = setString();

        cout<<"Podaj nazwe: ";
        name = setString();

        cout<<"Podaj poziom: ";
        lvl = setNumber<unsigned>();
        cout<<endl;

        NonPlayerCharacter it(instance, lvl);
        it.getName() = name;

        cout<<"Podaj szanse na drop: ";
        it.getChance() = setNumber<unsigned>();
        it.save();

        cout<<"Podaj ilo˜† pieni©dzy: ";
        it.getGold() = Gold(setNumber<int>());

        cout<<"Podaj ilo˜† do˜wiadczenia: ";
        it.addExp(setNumber<unsigned>());

        cout<<"Podaj regeneracje ¾ycia: ";
    	it.getRegenerationHp() = setNumber<int>();
        it.save();

        cout<<"Podaj obrone: ";
    	it.getDef() = setNumber<double>();
        it.save();

        cout<<"Podaj ile energii maskymalnej: ";
        it.getMaxEnergy() = setNumber<unsigned>();
        it.getEnergy() = it.getMaxEnergy();
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

        ofstream file_eq("bots/"+instance+"/"+instance+"_eq");
        for (unsigned i = 0; i < it.getInventory().max_size(); ++i)
        {
            cout<<"Podaj instancje przedmiotu (q - koniec): ";

            string temp = setString();
            if (temp == "q") break;

            file_eq<<temp<<endl;
        }
        file_eq.clear();
        file_eq.close();

        ofstream file("bots/"+instance+"/"+instance+"_dialogs");
        file<<"";
        file.clear();
        file.close();

        screen::clear();
        it.show();
        cout<<"Ukoäczono tworzenie postaci!\n\n[Dalej]";
        screen::paused();
    }
    cout<<"Gotowe!\n";
}