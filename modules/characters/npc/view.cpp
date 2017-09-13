#include "npc.hpp"

using namespace std;

void NonPlayerCharacter::show() const
{
    showLvl();
    Stats::show();
    viewHpForCharacters();
    viewEnergyForCharacters();
}

void NonPlayerCharacter::showPosibleAward() const
{
    cout<<"Nagroda za zabicie:"<<endl;
    cout<<"- "<<getExp()<<" doświadczenia"<<endl;
    cout<<"- ";
    goldView();
    cout<<endl;
    cout<<"- Przedmioty:\n";
    equipment.show();
}
