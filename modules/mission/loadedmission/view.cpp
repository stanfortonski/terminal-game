#include "loadedmission.hpp"

using namespace std;

void LoadedMission::showNeeds() const
{
    using namespace std;
    cout<<"Od "<<who<<endl;
    cout<<"\nZadanie: "<<name<<endl;

    for (unsigned i = 0; i < ORDERS_SIZE; ++i)
    {
        if (!ordersForMurder[i].first.empty())
            cout<<"Zabij: "<<ordersForMurder[i].second<<"/"<<must_kill[i]<<" "<<ordersForMurder[i].first<<endl;

        if (!orderedItems[i].empty())
            cout<<"Zdobądź przedmiot: "<<Item(orderedItems[i])<<endl;
    }
}

void LoadedMission::showAwards() const
{
    cout<<"Nagrody:\n";
    if ((const int &)gold > 0) cout<<"Złoto: "<<(const int &)gold<<endl;
    if (exp > 0) cout<<"Doświadczenie: "<<exp<<endl;
}
