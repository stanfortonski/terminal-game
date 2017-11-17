/***
* Author: Stasiek Forto≈Ñski
* Date: 01.06.2017
* Gold System
* Version: 1.2
***/

#ifndef GOLD_HPP_
#define GOLD_HPP_ 1
#include <iostream>

class Gold
{
	int gold = 0;

public:
	Gold(const int & g = 0): gold(g){}
	virtual ~Gold(){}

	bool enough(const Gold & obj) const{return gold >= obj.gold;}

	Gold & operator+=(const Gold & obj)
	{
		gold += obj.getGold();
		return *this;
	}
	Gold & operator-=(const Gold & obj)
	{
		gold -= obj.getGold();
		return *this;
	}
	operator int(){return gold;}
	int getGold() const{return gold;}
	int & getGold(){return gold;}

	void goldView() const
	{
		std::cout<<getGold()<<" zàota";
	}
};
#endif