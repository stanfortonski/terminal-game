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
    cout<<"1. Sprawdż swoje statystyki\n";
    cout<<"2. Popraw statystyki\n";
    cout<<"3. Ulepsz zdolności\n";
    cout<<"4. Otwórz inwentarz\n";
    cout<<"5. Fundusze\n";
    cout<<"6. Stół rzemieślniczy\n";
    cout<<"7. Zadania\n";
    cout<<"8. Powrót\n";
    cout<<"Wybierz działanie: ";
    switch (setNumber<unsigned>())
    {
        case 1:
            clear();
            show();
            cout<<endl<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Powrót]"<<Color::DEFAULT;
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

            cout<<endl<<endl<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Powrót]"<<Color::DEFAULT;
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
        cout<<"Twój ruch! Atakuj!\n\n";
        showCombat();

        cout<<"Wybierz działanie: ";
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
                    cout<<Color::FG_RED<<"\nBrak ci energi by wykonać ten ruch!\n\n"<<Color::DEFAULT;
                    cout<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Dalej]"<<Color::DEFAULT;
                    paused();
                }
            }
        }
    }
}
