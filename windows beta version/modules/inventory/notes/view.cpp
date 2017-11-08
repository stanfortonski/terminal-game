#include "notes.hpp"

using namespace std;

void eq::Notes::showRecipe(const unsigned & n) const
{
    cout<<n+1<<". "<<Item(recipes[n])<<endl<<endl;
}

void eq::Notes::show() const
{
    for (unsigned i = 0; i < recipes.size(); ++i)
        showRecipe(i);
}

unsigned eq::Notes::showComplex() const
{
    unsigned amount = 0;
    for (; amount < recipes.size(); ++amount)
    {
        showRecipe(amount);

        cout<<"Potrzebne skˆadniki:\n";
        Array arr = Item(recipes[amount]).getBuildingComponents();

        for (unsigned y = 0; y < arr.max_size(); ++y)
        {
            if (arr[y].empty()) continue;
            cout<<"- "<<Item(arr[y])<<endl;
        }
        cout<<endl;
    }
    return amount;
}