/***
* Author: Stasiek Fortoński
* Date: 29.05.2017
* Inventory
* Version: 2.1
***/

#ifndef INVENTORY_HPP_
#define INVENTORY_HPP_ 1
#include "user_equipment/user_equipment.hpp"
#include "notes/notes.hpp"
#include <vector>

class Trade;

namespace eq
{
	class Inventory
	{
		UserEquipment usedItems;
		Equipment<Item> items;
		Notes note;

	public:
		Inventory(){}
		explicit Inventory(Stats & st): usedItems(st.getInstance()+"_used_eq"), items(st.getInstance()+"_eq"), note(st.getInstance()+"_recipes"){}
		virtual ~Inventory(){}

		void save() const;
		void load(Stats & st);

		bool add(const Item & it);
		bool add(const Equipment<Item> & eq);
		bool pick(Stats & st, const unsigned & n);
		void unpick(Stats & st, const unsigned & n);
		int find(const string & instance) const{return items.find(instance);}
		unsigned getAmountOf(const string & instance) const{return items.getAmountOf(instance);}
		int findWithOut(const string & instance, std::vector<unsigned> & pos) const;
		
		void clear(){items.clear();}
		void putall(Stats & st){usedItems.putall(st);}

		void show() const;

		friend class InventoryController;
		friend class ::Trade;
		friend class Crafting;
	};
}
#endif