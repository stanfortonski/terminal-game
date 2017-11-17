#include "item.hpp"
#include "../libs/sets_types/sets_types.hpp"

using namespace std;

void Item::show() const
{
	cout<<"********* "<<Color::YELLOW<<getStringType()<<Color::DEFAULT<<" *********\n\n";

	if (!getRankName().empty())
	{
		getRankColor();
		cout<<getRankName()<<Color::DEFAULT<<endl;
	}

	if (!descriptions.empty())
		cout<<endl<<Color::MAGENTA<<newLine(descriptions)<<Color::DEFAULT<<endl<<endl;

    Stats::show();
    viewHpForItems();
    viewEnergyForItems();
    Needs::show();

    if (getValueType() == RECIPE)
    {
        cout<<"Pozwala stworzy†: "<<Item(getBuildingComponents()[0])<<endl;
    }

    cout<<"\n******************";
    for (unsigned i = 0; i <= getStringType().size(); ++i)
	   cout<<"*";
    cout<<endl;
}

void Item::showShort() const
{
    RankItem::getRankColor();
    cout<<getName();
    if (Needs::getNeedLvl() > 1)
        cout<<" "<<Needs::getNeedLvl()<<" lvl";
    cout<<Color::DEFAULT;
}

void Item::showPrice() const
{
    cout<<"Cena: ";
    goldView();
    cout<<endl;
}

std::ostream & operator<<(std::ostream & os, const Item & obj)
{
	obj.showShort();
	return os;
}