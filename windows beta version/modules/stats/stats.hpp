/***
* Author: Stasiek Fortoński
* Date: 21.05.2017
* Extended Statistic System With Save And load
* Version: 1.1.1
***/

#ifndef STATS_HPP_
#define STATS_HPP_ 1
#include <string>
#include <cstdlib>
#include "stats_upgrader/stats_upgrader.hpp"
#include "../gold/gold.hpp"
#include "../interpreter/basic_interpreter.hpp"

const std::string PLAYER_DIR ="players\\";
const std::string ITEM_DIR = "items\\";
const std::string NPC_DIR = "bots\\";

class Stats: public StatsUpgrader, public Gold, protected BasicInterpreter
{
public:
	Stats(){}
	explicit Stats(const std::string & fn): BasicInterpreter(fn)
	{
		load();
	}
	Stats(const std::string & dir, const std::string & fn): BasicInterpreter(dir+fn+"\\"+fn)
	{
		load();
		calcSill();
	}
	Stats(const std::string & dir, const std::string & fn, const std::string & name, const int & lvl): BasicInterpreter(dir+fn+"\\"+fn), StatsUpgrader(name, lvl)
	{
		if (system(string("mkdir "+dir+fn).c_str()) != -1);
		save();
	}
	virtual ~Stats(){}

	virtual void save() const;
	virtual void load();

	operator std::string() const {return getFileName();}
	std::string getInstance() const{return getFileName();}
	bool operator==(const Stats & st) const {return getInstance() == st.getInstance();}
	bool operator!=(const Stats & st) const {return !(*this == st);}

	virtual void viewCompare(const Stats & st) const;

	friend std::ostream & operator<<(std::ostream & os, const Stats & obj)
	{
		obj.showShort();
		return os;
	}
};
#endif