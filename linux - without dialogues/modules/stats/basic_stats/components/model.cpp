#include "components.hpp"

void HP::hurt(const double & val)
{
	points -= val - (defensive/2);
	if (isDead()) points = 0;
}

void HP::regenerateHp()
{
	points += maxPoints * (regeneratePoints/100);
	if (isFullHp()) points = maxPoints;
}

void Energy::regenerateEnergy()
{
	points += maxPoints * (regeneratePoints/100);
	if (isFullEnergy()) points = maxPoints;
}

bool chance(const int & val)
{
	if (val > 100) return true;
	else if (val < 0) return false;
	return (rand()%100+1) <= val;
}

bool Tricks::isDodged() const{return chance(dodge);}
bool Tricks::isBlocked() const{return chance(block);}
bool Tricks::isHitbacked() const{return chance(hitback);}
bool Damage::isCritical() const{return chance(critical);}

double Damage::getFullDamage() const
{
	double temp = (rand()%(dmgMax-dmgMin)) + dmgMin + 1;
	if (isCritical())
		temp += dmgMax * (criticalStr/100) + dmgMax;
	temp += strength/2;
	return temp;
}
