/***
* Author: Stasiek Fortoński
* Date: 18.05.2017
* Statistic System Extended By Level
* Version: 1.1.3
***/

#ifndef STATSUPGRADER_HPP_
#define STATSUPGRADER_HPP_ 1
#include "../basic_stats/basic_stats.hpp"

class StatsUpgrader: public BasicStats
{
	enum {MINDMG = 1, MAXDMG = 4, NEWLP = 6, HPUP = 20, TONEXTLVL = 500};

	unsigned level = 0;
	double experience = 0;
	double sill = 0;
	unsigned learnPoints = 0;

	void updateLvl();

	bool useLearnPoints(double & val);
	bool isNextLevel() const{return (experience >= sill) ? true : false;}

public:
	StatsUpgrader(){}
	StatsUpgrader(const std::string & str, const unsigned & lvl): BasicStats(str), level(lvl)
	{
		calcs();
	}
	virtual ~StatsUpgrader(){}

	bool addExp(const double & val);
	void upgraderControler();

	void showExp() const;
	void showLvl() const;
	void showLearnPoints() const;
	virtual void showShort() const;

	unsigned getLevel() const{return level;}

protected:
	void calcLearnPoints();
	void calcDmg();
	void calcHp();
	void calcs();
	void calcSill();

	double getExp() const{return experience;}
	double & getExp(){return experience;}

	unsigned getLvl() const{return level;}
	unsigned & getLvl() {return level;}

	double getSill() const{return sill;}
	double & getSill() {return sill;}

	unsigned getLp() const{return learnPoints;}
	unsigned & getLp() {return learnPoints;}
};
#endif