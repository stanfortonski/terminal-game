#include "skills.hpp"

using namespace std;

void Skills::showTreeName() const
{
    cout<<"*** "<<getCourseName()<<" ***"<<endl;
}

void Skills::showLearnPoints() const
{
    cout<<"Posiadasz punktów umiejętności: "<<learnPoints<<endl;
}
