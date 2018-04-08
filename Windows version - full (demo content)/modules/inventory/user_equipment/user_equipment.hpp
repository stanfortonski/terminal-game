/***
* Author: Stasiek Fortoński
* Date: 28.05.2017
* User Equipment
* Version: 3
***/

#ifndef USEREQUIPMENT_HPP_
#define USEREQUIPMENT_HPP_ 1
#include <array>
#include "../../item/item.hpp"
#include "../../stats/stats.hpp"

namespace eq
{
	static const unsigned AMOUNT_OF_USING_ITEMS = 7;

	class UserEquipment: private BasicInterpreter
	{
		std::array<Item, AMOUNT_OF_USING_ITEMS> items;

		std::string getTypeName(const unsigned & n) const
		{
			return TypeItem(TypeItem::Type(TypeItem::Type::WEAPON + n)).getStringType();
		}

	public:
		UserEquipment(){}
		UserEquipment(const std::string & fn): BasicInterpreter(fn){}
		virtual ~UserEquipment(){}

		void load(Stats & st);
		void save() const;

		void putall(Stats & st);

		bool pick(Stats & st, const Item & picked, Item & returned);
		Item unpick(Stats & st, const unsigned & n);

		void show() const;
		bool empty(const unsigned & n) const{return items[n].getInstance().empty();}

		Item & operator[](const unsigned & n){return items[n];}
		Item operator[](const unsigned & n) const{return items[n];}

		using BasicInterpreter::getFileName;
	};
}
#endif