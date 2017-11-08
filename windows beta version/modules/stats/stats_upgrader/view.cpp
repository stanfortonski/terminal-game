#include "stats_upgrader.hpp"
#include "../../libs/screen/screen.hpp"

using namespace std;
using namespace screen;

bool StatsUpgrader::addExp(const double & val)
{
	experience += val;

	if (isNextLevel())
	{
		cout<<"\nAwans na kolejny poziom!\n\n";;
		updateLvl();
		return true;
	}
	return false;
}

void StatsUpgrader::showExp() const
{
	cout<<"Do˜wiadczenie: "<<experience<<"/"<<sill<<endl;
}

void StatsUpgrader::showLvl() const
{
	cout<<"Poziom: "<<level<<endl;
}

void StatsUpgrader::showLearnPoints() const
{
	cout<<"Punkt¢w nauki: "<<learnPoints<<endl;
}

void StatsUpgrader::showShort() const
{
	cout<<getName()<<" "<<getLvl()<<" lvl";
}