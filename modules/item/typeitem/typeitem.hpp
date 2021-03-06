/***
* Author: Stasiek Forto�ski
* Date: 23.05.2017 - 11.06.2017
* Type Of Item
* Version: 1.0.3
***/

#ifndef TYPEITEM_HPP_
#define TYPEITEM_HPP_ 1
#include <iostream>

class TypeItem
{
public:
	enum Type{NORMAL, FOOD, WEAPON, SHIELD, HELMET, BODY_ARMOR, LEGS_ARMOR, RING, AMULET, RECIPE, QUEST};

private:
	Type type;

public:
	TypeItem(const Type & t = NORMAL): type(t){}
	virtual ~TypeItem(){}

	Type getValueType() const{return type;}
	Type & getValueType(){return type;}

	std::string getStringType() const
	{
		switch(type)
		{
			case FOOD: return "�ywno��";
			case WEAPON: return "Bro�";
			case SHIELD: return "Tarcza";
			case HELMET: return "He�m";
			case BODY_ARMOR: return "G�rny pancerz";
			case LEGS_ARMOR: return "Dolny pancerz";
			case RING: return "Pier�cie�";
			case AMULET: return "Amulet";
			case RECIPE: return "Przepis";
			case QUEST: return "Questowy";
			default: return "Zwyk�y";
		}
	}
};
#endif