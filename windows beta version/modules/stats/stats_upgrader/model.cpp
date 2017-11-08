#include "stats_upgrader.hpp"

using namespace std;

void StatsUpgrader::calcSill()
{
	sill = TONEXTLVL * level;
}

void StatsUpgrader::calcLearnPoints()
{
	learnPoints += NEWLP;
}

void StatsUpgrader::calcDmg()
{
	getMinDmg() += MINDMG;
 	getMaxDmg() += MAXDMG;
}

void StatsUpgrader::calcHp()
{
	double compare = getMaxHp() - ((level-1) * HPUP);
	if (compare < 0) compare = 0;
	getMaxHp() = getHp() = level * HPUP + compare;
}

void StatsUpgrader::calcs()
{
	calcSill();
	calcLearnPoints();
	calcHp();
	for (unsigned i = 1; i <= level; ++i)
		calcDmg();
}

void StatsUpgrader::updateLvl()
{
	++level;
	experience -= sill;
	calcSill();
	calcLearnPoints();
	calcHp();
	calcDmg();
	learnPoints += 5;
}

bool StatsUpgrader::useLearnPoints(double & val)
{
	if (learnPoints <= 0) return false;

	++val;
	--learnPoints;
	return true;
}