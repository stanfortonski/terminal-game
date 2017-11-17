#include "item.hpp"

bool Item::useBy(Stats & obj)
{
	if (!canUse(obj) || (getValueType() == Type::NORMAL)) return false;

	obj.onStats(*this);
	return true;
}

void Item::unUseBy(Stats & obj)
{
	obj.offStats(*this);
}

void Item::save() const
{
	Array temp = getBuildingComponents();
	Stats::save();
	BasicInterpreter::save("type", getValueType());
	BasicInterpreter::save("rank", RankItem::getRank());

	if (!descriptions.empty())
		BasicInterpreter::save("descriptions", descriptions);

	if (getNeedLvl() > 0)
		BasicInterpreter::save("needlvl", getNeedLvl());

	if (getNeedStr() > 0)
		BasicInterpreter::save("needstr", getNeedStr());

	if (getNeedDex() > 0)
		BasicInterpreter::save("needdex", getNeedDex());

	setBuildingComponents(temp);
}

void Item::load()
{
	Stats::load();

	int temp = 0;
	BasicInterpreter::load("type", temp);
	getValueType() = Type(temp);

	temp = 0;
	BasicInterpreter::load("rank", temp);
	RankItem::getRank() = Rank(temp);

	BasicInterpreter::load("descriptions", descriptions);
	BasicInterpreter::load("needlvl", getNeedLvl());
	BasicInterpreter::load("needstr", getNeedStr());
	BasicInterpreter::load("needdex", getNeedDex());
}

Array Item::getBuildingComponents() const
{
	Array arr;
	if (getValueType() == Type::RECIPE)
		BasicInterpreter::load("learn", arr[0]);

	for (unsigned i = 1; i < arr.max_size(); ++i)
		BasicInterpreter::load("component[" + std::to_string(i) + "]", arr[i]);
	return arr;
}

void Item::setBuildingComponents(const Array & arr) const
{
	if (getValueType() == Type::RECIPE)
		BasicInterpreter::save("learn", arr[0]);

	for (unsigned i = 1; i < arr.max_size(); ++i)
	{
		if (!arr[i].empty())
			BasicInterpreter::save("component[" + std::to_string(i) + "]", arr[i]);
	}
}