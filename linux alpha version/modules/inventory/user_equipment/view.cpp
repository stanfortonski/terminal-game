#include "user_equipment.hpp"

using namespace std;

void eq::UserEquipment::show() const
{
	for (unsigned i = 0; i < AMOUNT_OF_USING_ITEMS; ++i)
	{
		cout<<Color::FG_YELLOW<<i+1<<". "<<getTypeName(i)<<": "<<Color::DEFAULT;
		if (!empty(i)) cout<<items[i]<<endl;
		else cout<<"brak"<<endl;
	}
}
