#include "skills.hpp"

using namespace std;

void Skills::showTreeName() const
{
    cout<<"*** "<<getCourseName()<<" ***"<<endl;
}

void Skills::showLearnPoints() const
{
    cout<<"Posiadasz punkt¢w umiej©tno˜ci: "<<learnPoints<<endl;
}