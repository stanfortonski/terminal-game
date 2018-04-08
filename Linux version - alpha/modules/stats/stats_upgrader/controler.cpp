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
			cout<<"Teraz nie masz sił by poprawić swoją muskulature!\n\n";
			cout<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Powrót]"<<Color::DEFAULT;
			paused();
			return;
		}
		else
		{
			showLearnPoints();
			cout<<"1. Zwieksz siłe\n";
			cout<<"2. Zwieksz zręczność\n";
			cout<<"3. Zwieksz wytrzymałość\n";
			cout<<"4. Wróć\n";
			cout<<"Wybierz działanie: ";
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
