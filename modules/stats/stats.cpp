#include "stats.hpp"

void Stats::save() const
{
	std::ofstream file(BasicInterpreter::getFileName());
	file<<"";
	file.clear();
	file.close();

	BasicInterpreter::save("name", getName());

	if (getLvl() > 0)
		BasicInterpreter::save("lvl", getLvl());

	if (getExp() != 0)
		BasicInterpreter::save("exp", getExp());

	if (getLp() > 0)
		BasicInterpreter::save("learnpoints", getLp());

	if (getStr() != 0)
		BasicInterpreter::save("strength", getStr());

	if (getDex() != 0)
		BasicInterpreter::save("dexterity", getDex());

	if (getDef() != 0)
		BasicInterpreter::save("defense", getDef());

	if (getMinDmg() != 0)
		BasicInterpreter::save("dmgmin", getMinDmg());

	if (getMaxDmg() != 0)
		BasicInterpreter::save("dmgmax", getMaxDmg());

	if (getCrit() != 0)
		BasicInterpreter::save("crit", getCrit());

	if (getCritStr() != 0)
		BasicInterpreter::save("powercrit", getCritStr());

	if (getEnergy() != 0)
		BasicInterpreter::save("energymin", getEnergy());

	if (getMaxEnergy() != 0)
		BasicInterpreter::save("energymax", getMaxEnergy());

	if (getHp() != 0)
		BasicInterpreter::save("hpmin", getHp());

	if (getMaxHp() != 0)
		BasicInterpreter::save("hpmax", getMaxHp());

	if (getRegenerationHp() != 0)
		BasicInterpreter::save("hpreg", getRegenerationHp());

	if (getRegenerationEnergy() != 0)
		BasicInterpreter::save("energyreg", getRegenerationEnergy());

	if (getDodge() != 0)
		BasicInterpreter::save("dodge", getDodge());

	if (getBlock() != 0)
		BasicInterpreter::save("block", getBlock());

	if (getHitback() != 0)
		BasicInterpreter::save("hitback", getHitback());

	if (getGold() != 0)
		BasicInterpreter::save("gold", getGold());

	if (getPosition() != 0)
		BasicInterpreter::save("position", getPosition());
}

void Stats::load()
{
	BasicInterpreter::load("name", getName());
	BasicInterpreter::load("lvl", getLvl());
	BasicInterpreter::load("exp", getExp());
	BasicInterpreter::load("learnpoints", getLp());
	BasicInterpreter::load("strength", getStr());
	BasicInterpreter::load("dexterity", getDex());
	BasicInterpreter::load("defense", getDef());
	BasicInterpreter::load("dmgmin", getMinDmg());
	BasicInterpreter::load("dmgmax", getMaxDmg());
	BasicInterpreter::load("crit", getCrit());
	BasicInterpreter::load("powercrit", getCritStr());
	BasicInterpreter::load("energymin", getEnergy());
	BasicInterpreter::load("energymax", getMaxEnergy());
	BasicInterpreter::load("hpmin", getHp());
	BasicInterpreter::load("hpmax", getMaxHp());
	BasicInterpreter::load("hpreg", getRegenerationHp());
	BasicInterpreter::load("energyreg", getRegenerationEnergy());
	BasicInterpreter::load("dodge", getDodge());
	BasicInterpreter::load("block", getBlock());
	BasicInterpreter::load("hitback", getHitback());
	BasicInterpreter::load("gold", getGold());
	BasicInterpreter::load("position", getPosition());
}

void Stats::viewCompare(const Stats & st) const
{
	if (*this != st)
	{
		BasicStats::viewCompare(st);
	}
	else std::cout<<"Brak zmian.\n";
}