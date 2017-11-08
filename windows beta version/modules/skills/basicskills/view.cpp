#include "basicskills.hpp"

using namespace std;

string BasicSkills::getRomeLevel(const unsigned & n) const
{
   switch (level[n])
   {
       case 1: return "I";
       case 2: return "II";
       case 3: return "III";
       case 4: return "VI";
       case 5: return "V";
       case 6: return "VI";
       case 7: return "VII";
       case 8: return "VIII";
       case 9: return "IX";
       case 10: return "X";
   }
   return "";
}

void BasicSkills::show() const
{
    for (int i = 0; i < AMOUNT_SKILLS; ++i)
    {
        cout<<i+1<<". "<<names[i]<<" "<<getRomeLevel(i);
        if (energyTakes(i) > 0)
            cout<<"  energia: "<<energyTakes(i);
        cout<<endl;
    }
}