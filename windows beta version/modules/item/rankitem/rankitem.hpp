/***
* Author: Stasiek Fortoński
* Date: 01.06.2017
* Rank Item
* Version: 1.1
***/

#ifndef RANKITEM_HPP_
#define RANKITEM_HPP_ 1
#include "../../libs/screen/screen.hpp"

using screen::Color;

class RankItem
{
public:
	enum Rank{NORMAL, IMPROVED, IMPROVED_2, IMPROVED_3, IMPROVED_4, IMPROVED_5, RARE, RELIC, ARTIFACT};

private:
	Rank rank;

public:
	RankItem(const Rank & r = NORMAL): rank(r){}
	virtual ~RankItem(){}

	Rank getRank() const{return rank;}
	Rank & getRank(){return rank;}

	std::string getRankName() const
	{
		switch (rank)
		{
			case IMPROVED: return "Ulepszony";
			case IMPROVED_2: return "2x Ulepszony";
			case IMPROVED_3: return "3x Ulepszony";
			case IMPROVED_4: return "4x Ulepszony";
			case IMPROVED_5: return "5x Ulepszony";
			case RARE: return "Rzadki";
			case RELIC: return "Relikt";
			case ARTIFACT: return "Artefakt";
			default: return "";
		}
	}

	void getRankColor() const
	{
		switch (rank)
		{
			case NORMAL: break;
			case IMPROVED:
			case IMPROVED_2:
			case IMPROVED_3:
			case IMPROVED_4:
			case IMPROVED_5:
				std::cout<<Color::GREEN;
			break;
			case RARE: std::cout<<Color::BLUE; break;
			case RELIC: std::cout<<Color::CYAN; break;
			case ARTIFACT: std::cout<<Color::RED; break;
		}
	}
};
#endif