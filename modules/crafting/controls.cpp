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
    cout<<"1. Sprawdź liste przepisów\n";
    cout<<"2. Twórz\n";
    cout<<"3. Wróć\n";

    cout<<"Wybierz działanie: ";
    switch (setNumber<unsigned>())
    {
        case 1:
          clear();
          cout<<"Znane przepisy:\n\n";
          if (inv.note.showComplex() < 1) cout<<Color::FG_RED<<"Brak przepisów.\n"<<Color::DEFAULT<<endl;
          cout<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Powrót]"<<Color::DEFAULT;
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
              cout<<Color::FG_RED<<"Aby stworzyć przedmiot musisz poznać przepis!"<<Color::DEFAULT<<"\n\n";
              cout<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Powrót]"<<Color::DEFAULT;
              paused();
              return;
          }

          cout<<"Co chcesz stworzyć?\n";
          inv.note.show();
          cout<<"Wybierz przedmiot o id (wyjście - q): ";

          string option = toLowerCase(setString());
    	  if (option == "q") break;

          unsigned item_id = atoi(option.c_str())-1;

          if (inv.note.empty()) continue;
          else if (inv.note.size() <= item_id) continue;

          const Item & it(inv.note[item_id]);

          clear();

          if (whatIsMissing(inv, it))
          {
              cout<<"Posiadasz wszystkie składniki by stworzyć "<<it<<"."<<endl;
              cout<<"1. Stwórz\n";
              cout<<"2. Wróć\n";
              cout<<"Wybierz działanie: ";

              unsigned ch = setNumber<unsigned>();
              if (ch == 1)
              {
                  craft(inv, it);
                  clear();
                  cout<<Color::FG_GREEN<<"Pomyślnie utworzono przedmiot: "<<Color::DEFAULT<<it<<"!\n\n";
                  cout<<Color::BG_BLUE<<Color::FG_YELLOW<<"[OK]"<<Color::DEFAULT;
                  paused();
                  return;
              }
              else if (ch == 2) return;
          }
          else
          {
              cout<<endl<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Powrót]"<<Color::DEFAULT;
              paused();
              return;
          }
     }
}
