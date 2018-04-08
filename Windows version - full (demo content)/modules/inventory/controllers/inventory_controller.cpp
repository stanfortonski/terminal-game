#include "controllers.hpp"
#include "../../libs/sets_types/sets_types.hpp"
#include "../../libs/screen/screen.hpp"

using namespace std;
using namespace screen;

void eq::InventoryController::control(Inventory & inv, Stats & st)
{
	for (;;)
	{
		clear();
		inv.show();
		cout<<"\nWybierz przedmiot o id (wyj˜cie - q): ";

		string option = toLowerCase(setString());
		if (option == "q") break;
		unsigned n = atoi(option.c_str())-1;

		if (n > (inv.items.max_size() + AMOUNT_OF_USING_ITEMS-1));
		else if (n <= AMOUNT_OF_USING_ITEMS-1)
		{
			if (!inv.usedItems.empty(n))
				selectedUsed(inv, st, n);
		}
		else
		{
			n -= AMOUNT_OF_USING_ITEMS;
			if (inv.items.size() > n)
				selected(inv, st, n);
		}
	}
}

void eq::InventoryController::selectedUsed(Inventory & inv, Stats & st, const unsigned & n)
{
	clear();
	cout<<"Przedmiot: "<<inv.usedItems[n]<<endl;
	cout<<"\n1. Zdejmij przedmiot\n";
	cout<<"2. Przygl¥daj si© przedmiotowi\n";
	cout<<"3. Wyrzu† przedmiot\n";
	cout<<"4. Wr¢†\n";

	cout<<"Wybierz dziaˆanie: ";
	switch (setNumber<unsigned>())
	{
		case 1:
			inv.unpick(st, n);
			inv.save();
		break;

		case 2:
			clear();
			inv.usedItems[n].show();
			cout<<endl;
			cout<<Color::YELLOW<<"[Powr¢t]"<<Color::DEFAULT;
			paused();
		break;

		case 3:
			inv.usedItems.unpick(st, n);
			inv.save();
		break;
	}
}

void eq::InventoryController::showOption(Inventory & inv, Stats & st, const unsigned & n)
{
	switch (inv.items[n].getValueType())
	{
		case TypeItem::FOOD:
			cout<<"1. Spo¾yj to\n";
		break;

		case TypeItem::RECIPE:
			cout<<"1. Naucz si© przepisu\n";
		break;

		case TypeItem::NORMAL:
		case TypeItem::QUEST:
		break;

		default:
			if (inv.items[n].canUse(st))
				cout<<"1. U¾yj przedmiot\n";
			else cout<<Color::RED<<"Niespeˆniasz wymagaä do u¾ycia tego przedmiotu!\n"<<Color::DEFAULT;
	}
}

void eq::InventoryController::selected(Inventory & inv, Stats & st, const unsigned & n)
{
	clear();
	cout<<"Przedmiot: "<<inv.items[n]<<endl<<endl;
	showOption(inv, st, n);
	cout<<"2. Przygl¥daj si© przedmiotowi\n";
	cout<<"3. Ulepsz przedmiot\n";
	cout<<"4. Wyrzu† przedmiot\n";
	cout<<"5. Wr¢†\n";

	cout<<"Wybierz dziaˆanie: ";
	switch (setNumber<unsigned>())
	{
		case 1:
			if (!learningView(inv, n))
				inv.pick(st, n);
			inv.save();
		break;

		case 2:
			clear();
			inv.items[n].show();
			if (inv.items[n].getValueType() >= TypeItem::Type::WEAPON && inv.items[n].getValueType() < TypeItem::Type::RECIPE)
			{
				cout<<endl<<"Zmiany po u¾yciu tego przedmiotu:\n";
				inv.items[n].viewCompare(inv.usedItems[inv.items[n].getValueType() - 2]);
			}
			cout<<endl;
			cout<<Color::YELLOW<<"[Powr¢t]"<<Color::DEFAULT;
			paused();
		break;

		case 3:
			inv.items[n] = inv.items[n].improve((Gold &) st);
			inv.save();
		break;

		case 4:
			inv.items.pop_back(n);
			inv.save();
		break;
	}
}

bool eq::InventoryController::learningView(Inventory & inv, const unsigned & n)
{
	int learn = inv.note.learnRecipe(inv.items[n]);

	if (learn == 1)
	{
		inv.items.pop_back(n);
		clear();
		cout<<"Nauczyˆe˜ si© nowego przepisu!\n\n";
		cout<<Color::YELLOW<<"[Powr¢t]"<<Color::DEFAULT;
		paused();
		return true;
	}
	else if (learn == 0)
	{
		clear();
		cout<<"Ju¾ to wiem!\n\n";
		cout<<Color::YELLOW<<"[Powr¢t]"<<Color::DEFAULT;
		paused();
		return true;
	}
	return false;
}

void eq::InventoryController::picker(Inventory & inv, const Equipment<Item> & adds)
{
	if (adds.size() > 0 && !inv.items.isFull())
	{
		for (;;)
		{
			clear();
			cout<<"Przedmioty:\n";

			unsigned i = 0;
			for (; i < adds.size(); ++i)
				cout<<"- "<<adds[i]<<endl;

			cout<<"\n1. Biore wszystko\n";
			cout<<"2. Wybieram przedmiot kt¢ry wezm©\n";
			cout<<"3. Zostawiam wszystko\n";
			cout<<"Wybierz dziaˆanie: ";

			switch (setNumber<unsigned>())
			{
				case 1:
					if ((inv.items.size() + i) > inv.items.max_size())
					{
						cout<<Color::RED<<"Brak miejsca w ekwipunku by zabra† wszystko!\n"<<Color::DEFAULT;
						cout<<"Wybierz co we«miesz...\n\n";
						cout<<Color::YELLOW<<"[OK]"<<Color::DEFAULT;
						paused();
						chooseWasPick(inv, adds);
					}
					else inv.add(adds);
					return;

				case 2:
				 	chooseWasPick(inv, adds);
					return;

				case 3: return;
			}
		}
	}
}

void eq::InventoryController::chooseWasPick(Inventory & inv, const Equipment<Item> & adds)
{
	for (unsigned i = 0; i < adds.size(); ++i)
	{
		clear();
		cout<<"Przedmiot: "<<adds[i]<<endl;
		cout<<"\n1. Biore\n";
		cout<<"2. Zostawiam\n";
		cout<<"3. Zostawiam to i reszt©\n";
		cout<<"Wybierz dziaˆanie: ";

		switch (setNumber<unsigned>())
		{
			case 1:
				if (!inv.add(adds[i]))
				{
					cout<<Color::RED<<"Niestety ekwipunek jest ju¾ peˆny!\n\n"<<Color::DEFAULT;
					cout<<Color::YELLOW<<"[Powr¢t]"<<Color::DEFAULT;
					paused();
					return;
				}
			case 2: continue;
			default: --i; continue;
			case 3: return;
		}
	}
}