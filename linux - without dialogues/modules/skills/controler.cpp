#include "skills.hpp"
#include "../libs/sets_types/sets_types.hpp"
#include "../libs/screen/screen.hpp"

using namespace std;
using namespace screen;

void Skills::contolerTreeChoser()
{
  for (;;)
  {
      clear();
      cout<<"Wybierz swoją drogę umiejętności!\n\n";

      cout<<"1. Droga Cienia\n2. Droga Światła\n3. Droga Zrównoważona\nWybierz działanie: ";

      switch (setNumber<unsigned>())
      {
          case 1: getSkillType() = DARKNESS; set(); return;
          case 2: getSkillType() = LIGHT; set(); return;
          case 3: getSkillType() = MEDIUM; set(); return;
          default: continue;
      }
  }
}

void Skills::contolerUpgradeSkill()
{
  for (;;)
  {
    if (learnPoints > 0)
    {
      clear();
      showLearnPoints();
      cout<<endl;
      showTreeName();
      show();
      cout<<"5. Wróć\n";

      cout<<"Wybierz działanie: ";
      unsigned choice = setNumber<unsigned>();

      if (choice == 5) break;
      else if ((choice < 0) || (choice > AMOUNT_SKILLS)) continue;

      if (!upgrade(choice-1))
      {
          clear();
          cout<<Color::FG_RED<<"Jesteś już mistrzem w tej sztuce!\n\n"<<Color::DEFAULT;
          cout<<Color::BG_BLUE<<Color::FG_YELLOW<<"[OK]"<<Color::DEFAULT;
          paused();
      }
    }
    else
    {
        clear();
        cout<<Color::FG_RED<<"Brak ci sił by opanować nowe sztuki walki!\n\n"<<Color::DEFAULT;
        cout<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Powrót]"<<Color::DEFAULT;
        paused();
        break;
    }
  }
}
