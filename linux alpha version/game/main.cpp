#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../modules/item/item.hpp"
#include "../modules/inventory/inventory.hpp"
#include "../modules/libs/screen/screen.hpp"
#include "../modules/characters/player/player.hpp"
#include "../modules/characters/npc/npc.hpp"
#include "../modules/group/group.hpp"
#include "../modules/fight/fight.hpp"
#include "../modules/map/world/world.hpp"
#include "../modules/map/world/world.hpp"
#include "../modules/dialogue/dialogue.hpp"

using namespace std;
using namespace screen;

int main()
{
	srand(time(0));
	cout<<Color::DEFAULT;

	for (;;)
	{
		clear();
		cout<<"Czy posiadasz postać? (t/n): ";
		char choose = cin.get();
		cin.get();

		if (choose == 't') cout<<"* Ładowanie postaci *\n\n";
		else if (choose == 'n') cout<<"* Tworzenie postaci *\n\n";
		else continue;

		string imie;
		cout<<"Podaj nazwe postaci: ";
		getline(cin, imie);

		size_t found = imie.find_first_of("@#$%^&*()~?/<,.>\"\'|{[]}`+=;:-");
		if (found != std::string::npos)
		{
			clear();
			cout<<"Użyto niedozwolnych znaków w nazwie!\n\n";
			cout<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Powrót]"<<Color::DEFAULT;
			paused();
			continue;
		}

		Player * plr = nullptr;
		if (choose == 't')
		{
			ifstream file(PLAYER_DIR+imie+"/"+imie);
			if (!file.is_open())
			{
				clear();
				cout<<"Postać o podanej nazwie nie istnieje!\n\n";
				cout<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Powrót]"<<Color::DEFAULT;
				paused();
				continue;
			}
			file.clear();
			file.close();

			plr = new Player(imie);
		}
		else if (choose == 'n')
		{
			ifstream file(PLAYER_DIR+imie+"/"+imie);
			if (file.is_open())
			{
				clear();
				cout<<"Postać o podanej nazwie już istnieje!\n\n";
				cout<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Powrót]"<<Color::DEFAULT;
				paused();
				continue;
			}
			file.clear();
			file.close();

			plr = new Player(imie, 1);
		}

		Group our_team;
		our_team.push_back(new Player(*plr));
		delete plr;

		_map::World::get().enter(our_team);
		break;
	}
}
