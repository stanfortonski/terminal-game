/***
* Author: Stasiek Fortoński
* Date: 13.06.2017
* Player Note
* Version: 2
***/

#ifndef NOTES_HPP_
#define NOTES_HPP_ 1
#include "../equipment/equipment.hpp"
#include "../../item/item.hpp"

namespace eq
{
    class Notes
    {
        Equipment<std::string> recipes;

    public:
        Notes(){}
        Notes(const std::string & fn): recipes(fn){}
        virtual ~Notes(){}

        void load(){recipes.load();}
        void save() const{recipes.save();}

        int learnRecipe(const Item & it);

        std::string operator[](const unsigned & n) const{return recipes[n];}
        std::string & operator[](const unsigned & n){return recipes[n];}

        void show() const;
        void showRecipe(const unsigned & n) const;
        unsigned showComplex() const;

        bool empty() const{return recipes.empty();}
        unsigned size() const{return recipes.size();}
    };
}
#endif