/***
* Author: Stasiek Fortoñski
* Date: 16.05.2017
* Basic Statistic System
* Version: 1.2.1
***/

#ifndef BASICSTATS_HPP_
#define BASICSTATS_HPP_ 1
#include "components/components.hpp"

class BasicStats: public HP, public Energy, public Tricks, public Damage, public Dexterity
{
	std::string name;
	unsigned position = 1;

public:
	explicit BasicStats(const std::string & str = "nieznana"): name(str){}
	virtual ~BasicStats(){}

	void onStats(const BasicStats & st);
	void offStats(const BasicStats & st);

	virtual double combat(){return getFullDamage();}

	bool compare(const BasicStats & st);

	void showWithOutName() const;
	virtual void show() const;
	virtual void viewCompare(const BasicStats & st) const;

	friend bool operator<(const BasicStats & a, const BasicStats & b){return b.isFaster(a);}

	std::string getName() const{return name;}
	std::string & getName(){return name;}

	unsigned getPosition() const{return position;}
	unsigned & getPosition(){return position;}
};
#endif