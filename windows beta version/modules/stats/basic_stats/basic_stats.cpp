#include "basic_stats.hpp"

void BasicStats::onStats(const BasicStats & st)
{
	getMaxHp() += st.getMaxHp();
	getHp() += st.getHp();
	if (isFullHp()) getHp() = getMaxHp();

	getMaxEnergy() += st.getMaxEnergy();
	getEnergy() += st.getEnergy();
	if (isFullEnergy()) getEnergy() = getMaxEnergy();

	getStr() += st.getStr();
	getDef() += st.getDef();
	getDex() += st.getDex();
	getCrit() += st.getCrit();
	getCritStr() += st.getCritStr();
	getDodge() += st.getDodge();
	getHitback() += st.getHitback();
	getBlock() += st.getBlock();
	getRegenerationEnergy() += st.getRegenerationEnergy();
	getRegenerationHp() += st.getRegenerationHp();
	getMinDmg() += st.getMinDmg();
	getMaxDmg() += st.getMaxDmg();
}

void BasicStats::offStats(const BasicStats & st)
{
	getMaxHp() -= st.getMaxHp();
	getHp() -= st.getHp();
	if (isDead()) getHp() = 0;

	getMaxEnergy() -= st.getMaxEnergy();
	getEnergy() -= st.getEnergy();
	if (isEmptyEnergy()) getEnergy() = 0;

	getStr() -= st.getStr();
	getDef() -= st.getDef();
	getDex() -= st.getDex();
	getCrit() -= st.getCrit();
	getCritStr() -= st.getCritStr();
	getDodge() -= st.getDodge();
	getHitback() -= st.getHitback();
	getBlock() -= st.getBlock();
	getRegenerationEnergy() -= st.getRegenerationEnergy();
	getRegenerationHp() -= st.getRegenerationHp();
	getMinDmg() -= st.getMinDmg();
	getMaxDmg() -= st.getMaxDmg();
}

void BasicStats::showWithOutName() const
{
	Damage::show();
	Dexterity::show();
	HP::show();
	Energy::viewRegeneration();
	Tricks::show();
}

void BasicStats::show() const
{
	std::cout<<"Nazwa: "<<name<<std::endl;

	showWithOutName();
}

void BasicStats::viewCompare(const BasicStats & st) const
{
	std::cout<<std::showpos;
	BasicStats temp = *this;
	temp.offStats(st);
	temp.showWithOutName();
	temp.viewHpForItems();
	temp.viewEnergyForItems();
	std::cout<<std::noshowpos;
}