#include "stats_upgrader.hpp"
#include "../../libs/screen/screen.hpp"

using namespace std;
using namespace screen;

bool StatsUpgrader::addExp(const double & val)
{
	experience += val;

	if (isNextLevel())
	{
		cout<<"\nAwans na kolejny poziom!\n\n";
		cout<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Dalej]"<<Color::DEFAULT;
		paused();
		updateLvl();
		return true;
	}
	return false;
}

void StatsUpgrader::showExp() const
{
	cout<<"Doświadczenie: "<<experience<<"/"<<sill<<endl;
}

void StatsUpgrader::showLvl() const
{
	cout<<"Poziom: "<<level<<endl;
}

void StatsUpgrader::showLearnPoints() const
{
	cout<<"Punktów nauki: "<<learnPoints<<endl;
}

void StatsUpgrader::showShort() const
{
	cout<<getName()<<" "<<getLvl()<<" lvl";
}
