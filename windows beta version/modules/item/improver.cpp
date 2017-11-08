#include "item.hpp"
#include "../libs/screen/screen.hpp"

using namespace std;
using namespace screen;

Item & Item::improve(Gold & gold)
{
	if (gold.enough(getGold()))
	{
		if (checkRank() == -1)
		{
			clear();
			cout<<Color::RED<<"Nie mo¾esz ulepszy† tego przedmiotu!\n"<<Color::DEFAULT;
			cout<<endl<<Color::YELLOW<<"[Powr¢t]"<<Color::DEFAULT;
			paused();
			return *this;
		}
		double toBeat = setValueImprove();

		gold.getGold() -= getGold();
		RankItem::getRank() = Rank(RankItem::getRank()+1);

		toBeat = toBeat/100 + 1;
		getStr() *= toBeat;
		getHp() *= toBeat;
		getMaxHp() *= toBeat;
		getDef() *= toBeat;
		getDex() *= toBeat;
		getCrit() *= toBeat;
		getCritStr() *= toBeat;
		getDodge() *= toBeat;
		getHitback() *= toBeat;
		getBlock() *= toBeat;
		getRegenerationEnergy() *= toBeat;
		getRegenerationHp() *= toBeat;
		getEnergy() *= toBeat;
		getMaxEnergy() *= toBeat;
		getMinDmg() *= toBeat;
		getMaxDmg() *= toBeat;
		getGold() = (getGold() * 2);

		getFileName() += "I";
		ofstream file(getFileName());
		file<<"";
		file.clear();
		file.close();
		
		save();

		clear();
		cout<<"Ulepszono przedmiot!\n";
		cout<<endl<<Color::YELLOW<<"[Powr¢t]"<<Color::DEFAULT;
		paused();
	}
	else
	{
		clear();
		cout<<Color::RED<<"Potrzebujesz ";
		goldView();
		cout<<" by ulepszy† ten przedmiot!\n"<<Color::DEFAULT;
		cout<<endl<<Color::YELLOW<<"[Powr¢t]"<<Color::DEFAULT;
		paused();
	}
	return *this;
}


int Item::checkRank() const
{
	switch (RankItem::getRank())
	{
		case Rank::NORMAL: return Rank::NORMAL;
		case Rank::IMPROVED: return Rank::IMPROVED;
		case Rank::IMPROVED_2: return Rank::IMPROVED_2;
		case Rank::IMPROVED_3: return Rank::IMPROVED_3;
		case Rank::IMPROVED_4: return Rank::IMPROVED_4;
		default: return -1;
	}
}

double Item::setValueImprove() const
{
	switch (RankItem::getRank())
	{
		case Rank::NORMAL: return 3;
		case Rank::IMPROVED: return 5;
		case Rank::IMPROVED_2: return 10;
		case Rank::IMPROVED_3: return 15;
		case Rank::IMPROVED_4: return 25;
		default: return -1;
	}
}