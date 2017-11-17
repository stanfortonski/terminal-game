#include "components.hpp"

double HP::hurt(const double & val)
{
	double dmg  = val - (defensive/3);
	if (dmg <= 1) dmg = 1;
	
	points -= dmg;
	if (isDead()) points = 0;
	
	return dmg;
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