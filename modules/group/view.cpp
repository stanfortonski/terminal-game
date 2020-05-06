#include "group.hpp"

using namespace std;

void Group::show() const
{
    for (unsigned i = 0; i < amount; ++i)
    {
        std::cout<<i+1<<". ";
        if (mate[i]->isDead()) std::cout<<"(nie ¾yje) ";
        cout<<*mate[i]<<"\t";
        mate[i]->viewHpForCharacters();
    }
}

void Group::showAdd(Stats * st) const
{
    cout<<"Czy doda† "<<Color::GREEN<<st->getName()<<Color::DEFAULT<<" do grupy ?\n";
    cout<<"1. Tak\n2. Nie\n";
}