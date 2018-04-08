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

string setName()
{
	string name;
	cout<<"Podaj nazwe postaci: ";
	getline(cin, name);

	size_t found = name.find_first_of("@#$%^&*()~?/<,.>\"\'|{[]}`+=;:");
	if (found != std::string::npos)
	{
		clear();
		cout<<"U¾yto niedozwolnych znak¢w w nazwie!\n\n";
		cout<<Color::YELLOW<<"[Powr¢t]"<<Color::DEFAULT;
		paused();
		return "";
	}
	return name;
}

bool isPlayerSet(const string & name)
{
	ifstream file(PLAYER_DIR+name+"\\"+name);
	if (file.is_open()) return true;
	file.clear();
	file.close();
	return false;
}

int main()
{
	srand(time(0));
	cout<<Color::DEFAULT;
	
	message("Terminal-Game Full by Stasiek Fortoäski 2017r.", 50);
	cout<<endl<<endl<<Color::YELLOW<<"[Start]"<<Color::DEFAULT;
	paused();
	
	int choose;
	Player * plr = nullptr;
	
	for (;;)
	{
		clear();
		cout<<"Czy posiadasz posta†? (t/n/q): ";
		char key = cin.get();
		cin.get();
		
		if (key == 't' || key == 'T') {
			cout<<"* adowanie postaci *\n\n";
			choose = 1;
		}
		else if (key == 'n' || key == 'N') 
		{
			cout<<"* Tworzenie postaci *\n\n";
			choose = 0;
		}
		else if (key == 'q' || key == 'Q') break;
		else{
			cin.clear();
			while(cin.get() != '\n') continue;
			continue;
		}

		string name = setName();
		if (name.empty()) continue;

		if (choose == 1)
		{
			if (!isPlayerSet(name))
			{
				clear();
				cout<<"Posta† o podanej nazwie nie istnieje!\n\n";
				cout<<Color::YELLOW<<"[Powr¢t]"<<Color::DEFAULT;
				paused();
				continue;
			}
			plr = new Player(name);
		}
		else if (choose == 0)
		{
			if (isPlayerSet(name))
			{
				clear();
				cout<<"Posta† o podanej nazwie ju¾ istnieje!\n\n";
				cout<<Color::YELLOW<<"[Powr¢t]"<<Color::DEFAULT;
				paused();
				continue;
			}
			plr = new Player(name, 1);
		}

		Group our_team;
		our_team.push_back(new Player(*plr));
		delete plr;
		plr = nullptr;
		
		_map::World::get().enter(our_team);
	}
}