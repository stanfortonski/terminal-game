/***
* Author: Stasiek Fortoński
* Date: 23.05.2017
* Item System
* Version: 1.5
***/

#ifndef ITEM_HPP_
#define ITEM_HPP_ 1
#include <array>
#include "needs/needs.hpp"
#include "typeitem/typeitem.hpp"
#include "rankitem/rankitem.hpp"

typedef std::array<std::string, 11> Array;

class Item: public Stats, public TypeItem, public Needs, private RankItem
{
	std::string descriptions;

	int checkRank() const;
	double setValueImprove() const;

public:
	Item(){}
	Item(const std::string & instance): Stats(instance)
	{
		load();
	}
	Item(const std::string & instance, const std::string & name, const Type & val, const Rank & rank, const std::string & desc, const int & l = 0, const int & s = 0, const int & d = 0)
	: Stats(ITEM_DIR, instance, name, 0), TypeItem(val), RankItem(rank), descriptions(desc), Needs(l, s, d)
	{
		save();
	}
	virtual ~Item(){}

	virtual void save() const;
	virtual void load();

	bool useBy(Stats & obj);
	void unUseBy(Stats & obj);

	Item & improve(Gold & gold);
	Array getBuildingComponents() const;
	void setBuildingComponents(const Array & arr) const;

	std::string getDescriptions() const{return descriptions;}

	virtual void show() const;
	void showShort() const;
	void showPrice() const;

	friend std::ostream & operator<<(std::ostream & os, const Item & obj);
};
#endif
