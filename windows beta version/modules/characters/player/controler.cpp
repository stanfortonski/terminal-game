#include "player.hpp"
#include "../../libs/sets_types/sets_types.hpp"
#include "../../libs/screen/screen.hpp"
#include <cmath>

using namespace std;
using namespace screen;

void Player::characterControler()
{
  for (;;)
  {
    clear();
    cout<<"1. Sprawd¾ swoje statystyki\n";
    cout<<"2. Popraw statystyki\n";
    cout<<"3. Ulepsz zdolno˜ci\n";
    cout<<"4. Otw¢rz inwentarz\n";
    cout<<"5. Fundusze\n";
    cout<<"6. St¢ˆ rzemie˜lniczy\n";
    cout<<"7. Zadania\n";
    cout<<"8. Powr¢t\n";
    cout<<"Wybierz dziaˆanie: ";
    switch (setNumber<unsigned>())
    {
        case 1:
            clear();
            show();
            cout<<endl<<Color::YELLOW<<"[Powr¢t]"<<Color::DEFAULT;
            paused();
        break;

        case 2:
            upgraderControler();
            save();
        break;

        case 3:
            Skills::contolerUpgradeSkill();
            save();
        break;

        case 4:
            eq::InventoryController::get().control(inventory, *this);
            save();
        break;

        case 5:
            clear();
            cout<<"Posiadane fundusze: ";
            goldView();

            cout<<endl<<endl<<Color::YELLOW<<"[Powr¢t]"<<Color::DEFAULT;
            paused();
        break;

        case 6:
            eq::Crafting::get().control(inventory);
            inventory.save();
        break;

        case 7:
            Quests::control();
            Quests::save();
        break;

        case 8:
            return;
    }
  }
}

double Player::combat()
{
    double dmg = getFullDamage();

    for (;;)
    {
        clear();
        cout<<"Tw¢j ruch! Atakuj!\n\n";
        showCombat();

        cout<<"Wybierz dziaˆanie: ";
        unsigned choice = setNumber<unsigned>()-1;

        for (unsigned i = 0; i < BasicSkills::AMOUNT_SKILLS; ++i)
        {
            if (choice == i)
            {
                if (getEnergy() >= Skills::energyTakes(i))
                {
                    getEnergy() -= Skills::energyTakes(i);
                    return round(dmg + dmg * Skills::getSkill(i));
                }
                else
                {
                    cout<<Color::RED<<"\nBrak ci energi by wykona† ten ruch!\n\n"<<Color::DEFAULT;
                    cout<<Color::YELLOW<<"[Dalej]"<<Color::DEFAULT;
                    paused();
                }
            }
        }
    }
}