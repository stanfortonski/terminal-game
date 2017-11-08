#include "user_equipment.hpp"
#include <fstream>

using namespace std;

void eq::UserEquipment::load(Stats & st)
{
	for (unsigned i = 0; i < AMOUNT_OF_USING_ITEMS; ++i)
	{
		string temp;
		BasicInterpreter::load(getTypeName(i), temp);

		if (temp.empty()) continue;

		Item it;
		pick(st, Item(temp), it);
	}
}

void eq::UserEquipment::putall(Stats & st)
{
	for (unsigned i = 0; i < AMOUNT_OF_USING_ITEMS; ++i)
		unpick(st, i);
}

void eq::UserEquipment::save() const
{
	ofstream file(BasicInterpreter::getFileName());
	file<<"";
	file.clear();
	file.close();

	for (unsigned i = 0; i < AMOUNT_OF_USING_ITEMS; ++i)
	{
		if (!empty(i))
			BasicInterpreter::save(getTypeName(i), items[i].getInstance());
	}
}

bool eq::UserEquipment::pick(Stats & st, const Item & picked, Item & returned)
{
	int n = picked.getValueType();
	if (n >= TypeItem::Type::WEAPON)
	{
		if (picked.canUse(st))
		{
			n -= 2;
			if (!empty(n))
				returned = unpick(st, n);

			items[n] = picked;
			items[n].useBy(st);
			return true;
		}
	}
	return false;
}

Item eq::UserEquipment::unpick(Stats & st, const unsigned & n)
{
	Item temp;
	if (!empty(n))
	{
		temp = items[n];
		items[n].unUseBy(st);
		items[n] = Item();
	}
	return temp;
}