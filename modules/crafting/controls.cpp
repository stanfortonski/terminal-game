#include "crafting.hpp"
#include "../libs/sets_types/sets_types.hpp"
#include "../libs/screen/screen.hpp"

using namespace std;
using namespace screen;

void eq::Crafting::control(Inventory & inv)
{
  for (;;)
  {
    inv.save();
    clear();
    cout<<"1. Sprawd« liste przepis¢w\n";
    cout<<"2. Tw¢rz\n";
    cout<<"3. Wr¢†\n";

    cout<<"Wybierz dziaˆanie: ";
    switch (setNumber<unsigned>())
    {
        case 1:
          clear();
          cout<<"Znane przepisy:\n\n";
          if (inv.note.showComplex() < 1) cout<<Color::RED<<"Brak przepis¢w.\n"<<Color::DEFAULT<<endl;
          cout<<Color::YELLOW<<"[Powr¢t]"<<Color::DEFAULT;
          paused();
          return;

        case 2:
          maker(inv);
          return;

        case 3:
          return;
    }
  }
}

void eq::Crafting::maker(Inventory & inv)
{
    for (;;)
    {
          clear();
          if (inv.note.empty())
          {
              cout<<Color::RED<<"Aby stworzy† przedmiot musisz pozna† przepis!"<<Color::DEFAULT<<"\n\n";
              cout<<Color::YELLOW<<"[Powr¢t]"<<Color::DEFAULT;
              paused();
              return;
          }

          cout<<"Co chcesz stworzy†?\n";
          inv.note.show();
          cout<<"Wybierz przedmiot o id (wyj˜cie - q): ";

          string option = toLowerCase(setString());
    	  if (option == "q") break;

          unsigned item_id = atoi(option.c_str())-1;

          if (inv.note.empty()) continue;
          else if (inv.note.size() <= item_id) continue;

          const Item & it(inv.note[item_id]);

          clear();

          if (whatIsMissing(inv, it))
          {
              cout<<"Posiadasz wszystkie skˆadniki by stworzy† "<<it<<"."<<endl;
              cout<<"1. Stw¢rz\n";
              cout<<"2. Wr¢†\n";
              cout<<"Wybierz dziaˆanie: ";

              unsigned ch = setNumber<unsigned>();
              if (ch == 1)
              {
                  craft(inv, it);
                  clear();
                  cout<<Color::GREEN<<"Pomy˜lnie utworzono przedmiot: "<<Color::DEFAULT<<it<<"!\n\n";
                  cout<<Color::YELLOW<<"[OK]"<<Color::DEFAULT;
                  paused();
                  return;
              }
              else if (ch == 2) return;
          }
          else
          {
            cout<<endl<<Color::YELLOW<<"[Powr¢t]"<<Color::DEFAULT;
            paused();
            return;
          }
     }
}