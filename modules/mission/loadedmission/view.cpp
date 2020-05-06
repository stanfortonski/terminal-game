#include "loadedmission.hpp"
#include "../../characters/npc/npc.hpp"

using namespace std;

void LoadedMission::showNeeds() const
{
	size_t found = who.find_last_of("/\\");
	cout<<"Zadanie: "<<name<<endl;
    cout<<"Od "<<NonPlayerCharacter(who.substr(found+1))<<endl<<endl;

	eq::Equipment<Item> eq;
	for (unsigned i = 0; i < ORDERS_SIZE; ++i)
    {
		if (!orderedItems[i].empty())
			eq.push_back(Item(orderedItems[i]));
	}
	
	vector<string> befores;
	for (unsigned i = 0; i < eq.size(); ++i)
	{
		bool next = false;
		for (unsigned y = 0; y < befores.size(); ++y)
		{
			if (eq[i].getInstance() == befores[y]) 
				next = true;
		}
		if (next) continue;
		
		cout<<"Zdob¥d«: "<<eq[i]<<" "<<eq.getAmountOf(eq[i].getInstance())<<"x"<<endl;
		befores.push_back(eq[i].getInstance());
	}
	
    for (unsigned i = 0; i < ORDERS_SIZE; ++i)
    {
		if (!ordersForMurder[i].first.empty())
            cout<<"\nZabij: "<<killed[i]<<"/"<<ordersForMurder[i].second<<" "<<ordersForMurder[i].first;
		
	}
}

void LoadedMission::showAwards() const
{
    cout<<"Nagrody:\n";
    if ((const int &)gold > 0) cout<<"Zˆoto: "<<(const int &)gold<<endl;
    if (exp > 0) cout<<"Do˜wiadczenie: "<<exp<<endl;
}