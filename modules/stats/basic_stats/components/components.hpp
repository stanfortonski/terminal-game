/***
* Author: Stasiek Fortoñski
* Date: 16.05.2017
* Components of Basic Stats
* Version: 1.2
***/

#ifndef COMPONENTS_HPP_
#define COMPONENTS_HPP_ 1
#include <iostream>
#include <cstdlib>

class HP
{
	long points = 0;
	long maxPoints = 0;
	double defensive = 0;
	int regeneratePoints = 0;

public:
	HP(){}
	virtual ~HP(){}

	double hurt(const double & val);
	void regenerateHp();

	bool isDead() const{return points <= 0;}
	bool isFullHp() const{return points >= maxPoints;}

	virtual void show() const;
	void viewHpForCharacters() const;
	void viewHpForItems() const;

	long getHp() const{return points;}
	long & getHp(){return points;}

	long getMaxHp() const{return maxPoints;}
	long & getMaxHp(){return maxPoints;}

	int getRegenerationHp() const{return regeneratePoints;}
	int & getRegenerationHp(){return regeneratePoints;}

	double getDef() const{return defensive;}
	double & getDef(){return defensive;}
};


class Energy
{
	unsigned points = 0;
	unsigned maxPoints = 0;
	int regeneratePoints = 0;

public:
	Energy(){}
	virtual ~Energy(){}

	bool isEmptyEnergy() const{return points <= 0;}
	bool isFullEnergy() const{return points >= maxPoints;}

	void regenerateEnergy();

	void viewRegeneration() const;
	void viewEnergyForCharacters() const;
	void viewEnergyForItems() const;

	unsigned getEnergy() const{return points;}
	unsigned & getEnergy(){return points;}

	unsigned getMaxEnergy() const{return maxPoints;}
	unsigned & getMaxEnergy(){return maxPoints;}

	int getRegenerationEnergy()const{return regeneratePoints;}
	int & getRegenerationEnergy(){return regeneratePoints;}
};


class Tricks
{
	int dodge = 0;
	int block = 0;
	int hitback = 0;

public:
	Tricks(){}
	virtual ~Tricks(){}

	bool isDodged() const;
	bool isBlocked() const;
	bool isHitbacked() const;

	virtual void show() const;

	int getDodge() const{return dodge;}
	int & getDodge(){return dodge;}

	int getBlock() const{return block;}
	int & getBlock(){return block;}

	int getHitback() const{return hitback;}
	int & getHitback(){return hitback;}
};


class Damage
{
	double strength = 0;
	int dmgMin = 0;
	int dmgMax = 0;
	int critical = 0;
	int criticalStr = 0;

public:
	Damage(){}
	virtual ~Damage(){}

	double getFullDamage() const;
	bool isCritical() const;

	virtual void show() const;

	double getStr() const{return strength;}
	double & getStr(){return strength;}

	int getMinDmg() const{return dmgMin;}
	int & getMinDmg(){return dmgMin;}

	int getMaxDmg() const{return dmgMax;}
	int & getMaxDmg(){return dmgMax;}

	int getCrit() const{return critical;}
	int & getCrit(){return critical;}

	int getCritStr() const{return criticalStr;}
	int & getCritStr(){return criticalStr;}
};


class Dexterity
{
	double points = 0;

public:
	Dexterity(){}
	virtual ~Dexterity(){}

	bool isFaster(const Dexterity & st) const{return points >= st.points;}

	virtual void show() const;

	double getDex() const{return points;}
	double & getDex(){return points;}
};
#endif