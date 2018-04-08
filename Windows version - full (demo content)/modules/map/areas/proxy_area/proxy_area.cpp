#include "proxy_area.hpp"

using namespace std;
using namespace screen;

void _map::ProxyArea::show() const
{
    cout<<Color::GREEN<<name<<Color::DEFAULT<<endl;
    cout<<desc<<endl;
    if (!desc.empty()) cout<<endl;
}

void _map::ProxyArea::viewWays() const
{
    for (unsigned i = 0; i < amountOfWays(); ++i)
    {
        cout<<i+1<<". "<<here->getPlace(i).getName();
        int lvl = getPlace(i).getMinimalLVL();
        if (lvl != 0) cout<<" (od "<<lvl<<" poziomu)";
        cout<<endl;
    }
}

void _map::ProxyArea::viewNpcNames() const
{
    vector<string> instances = npcInstances;
    for (unsigned i = 0; i < instances.size(); ++i)
        cout<<i+1<<". "<<NonPlayerCharacter(instances[i])<<endl;
}