#include "stats_upgrader.hpp"
#include "../../libs/sets_types/sets_types.hpp"
#include "../../libs/screen/screen.hpp"

using namespace std;
using namespace screen;

void StatsUpgrader::upgraderControler()
{
	for (;;)
	{
		clear();
		if (learnPoints <= 0)
		{
			cout<<Color::RED<<"Teraz nie masz siˆy by poprawi† swoj¥ muskulature!\n\n"<<Color::DEFAULT;
			cout<<Color::YELLOW<<"[Powr¢t]"<<Color::DEFAULT;
			paused();
			return;
		}
		else
		{
			showLearnPoints();
			cout<<"1. Zwieksz siˆe\n";
			cout<<"2. Zwieksz zr©czno˜†\n";
			cout<<"3. Zwieksz wytrzymaˆo˜†\n";
			cout<<"4. Wr¢†\n";
			cout<<"Wybierz dziaˆanie: ";
			switch (setNumber<unsigned>())
			{
				case 1:
					useLearnPoints(getStr());
				break;

				case 2:
					useLearnPoints(getDex());
				break;

				case 3:
					useLearnPoints(getDef());
				break;

				case 4:
					return;
			}
		}
	}
}