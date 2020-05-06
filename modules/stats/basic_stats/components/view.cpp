#include "components.hpp"
#include <cmath>

using namespace std;

void HP::viewHpForCharacters() const
{
	cout<<"Hp: "<<round(points*100/maxPoints)<<"% ("<<points<<"/"<<maxPoints<<")"<<endl;
}

void HP::viewHpForItems() const
{
	if (maxPoints != 0)
		cout<<"½ycie maksymalne: "<<maxPoints<<endl;

	if (points != 0)
		cout<<"Przywraca punkt¢w ¾ycia: "<<points<<endl;
}

void HP::show() const
{
	if (defensive != 0)
		cout<<"Obrona: "<<defensive<<endl;

	if (regeneratePoints != 0)
		cout<<"Regeneracja ¾ycia: "<<regeneratePoints<<"%"<<endl;
}

void Energy::viewEnergyForCharacters() const
{
	cout<<"Energia: "<<points<<"/"<<maxPoints<<endl;
}

void Energy::viewEnergyForItems() const
{
	if (maxPoints != 0)
		cout<<"Energia maksymalna: "<<maxPoints<<endl;

	if (points != 0)
		cout<<"Przywraca energie: "<<points<<endl;
}

void Energy::viewRegeneration() const
{
	if (regeneratePoints != 0)
		cout<<"Regeneracja energi: "<<regeneratePoints<<"%"<<endl;
}

void Tricks::show() const
{
	if (dodge != 0)
		cout<<"Szansa na unik: "<<dodge<<"%"<<endl;

	if (block != 0)
		cout<<"Szansa na blok: "<<block<<"%"<<endl;

	if (hitback != 0)
		cout<<"Szansa na konstratak: "<<hitback<<"%"<<endl;
}

void Damage::show() const
{
	if (dmgMax != 0)
	{
		if (dmgMin == dmgMax)
			cout<<"Obra¾enia: "<<dmgMax<<endl;
		else
			cout<<"Obra¾enia: "<<dmgMin<<" - "<<dmgMax<<endl;
	}

	if (critical != 0)
		cout<<"Szansa na cios krytyczny: "<<critical<<"%"<<endl;

	if (criticalStr != 0)
		cout<<"Siˆa ciosu krytycznego: "<<criticalStr+100<<"%"<<endl;

	if (strength != 0)
		cout<<"Siˆa: "<<strength<<endl;
}

void Dexterity::show() const
{
	if (points != 0)
		cout<<"Zr©czno˜†: "<<points<<endl;
}