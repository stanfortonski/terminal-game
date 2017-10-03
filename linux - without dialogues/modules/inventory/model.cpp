#include "inventory.hpp"

void eq::Inventory::save() const
{
	items.save();
	usedItems.save();
	note.save();
}

void eq::Inventory::load(Stats & st)
{
	items.load();
	usedItems.load(st);
	note.load();
}

bool eq::Inventory::add(const Item & it)
{
	if (items.isFull()) return false;
	items.push_back(it);
	return true;
}

bool eq::Inventory::add(const Equipment<Item> & eq)
{
	if (items.isFull()) return false;
	items.push_back(eq);
	return true;
}

bool eq::Inventory::pick(Stats & st, const unsigned & n)
{
	Item temp;
	if (items[n].getValueType() == TypeItem::Type::FOOD)
	{
		items[n].useBy(st);
		items.pop_back(n);
		return true;
	}
	else if (usedItems.pick(st, items[n], temp))
	{
		items.pop_back(n);
		if (!temp.getInstance().empty()) add(temp);
		return true;
	}
	return false;
}

void eq::Inventory::unpick(Stats & st, const unsigned & n)
{
	add(usedItems.unpick(st, n));
}

int eq::Inventory::find(const string & instance) const
{
	for (unsigned i = 0; i < items.size(); ++i)
	{
		if (items[i].getInstance() == instance)
			return i;
	}
	return -1;
}
