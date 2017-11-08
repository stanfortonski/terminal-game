/***
* Author: Stasiek Fortoäski
* Date: 23.05.2017
* Requirements To Use Item
* Version: 2
***/

#ifndef NEEDS_HPP_
#define NEEDS_HPP_ 1
#include "../../stats/stats.hpp"
#include "../../libs/screen/screen.hpp"

using screen::Color;

class Needs
{
	unsigned lvl = 1;
	int strength;
	int dexterity;

public:
	Needs(const int & l = 1, const int & s = 0, const int & d = 0): lvl(l), strength(s), dexterity(d){}
	virtual ~Needs(){}

	bool canUse(Stats & obj) const
	{
		return ((obj.getLevel() >= lvl) && (obj.getStr() >= strength) && (obj.getDex() >= dexterity));
	}

	virtual void show() const
	{
		if ((lvl > 1) || (strength > 0) || (dexterity > 0))
		{
			std::cout<<Color::RED<<"\nWymagania:\n";
			if (lvl > 1)
				std::cout<<"* Poziom: "<<lvl<<std::endl;

			if (strength > 0)
				std::cout<<"* Siˆa: "<<strength<<std::endl;

			if (dexterity > 0)
				std::cout<<"* Zr©czno˜†: "<<dexterity<<std::endl;
		}
		std::cout<<Color::DEFAULT;
	}

protected:
	unsigned getNeedLvl()const{return lvl;}
	unsigned & getNeedLvl(){return lvl;}

	int getNeedStr()const{return strength;}
	int & getNeedStr(){return strength;}

	int getNeedDex()const{return dexterity;}
	int & getNeedDex(){return dexterity;}
};
#endif