/***
* Author: Stasiek Forto≈Ñski
* Date: 27.05.2017
* Equipment
* Version: 2.1
***/

#ifndef EQUIPMENT_HPP_
#define EQUIPMENT_HPP_ 1
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include "../../item/item.hpp"
#include "../../libs/screen/screen.hpp"

namespace eq
{
	template <class T>
	class Equipment: public std::vector<T>
	{
		typedef std::vector<T> Vector;
		static const unsigned MAX_SIZE = 60;
		std::string fileName;

	public:
		Equipment(){}
		Equipment(const std::string & fn): fileName(fn){}
		virtual ~Equipment(){}

		void save() const
		{
			std::ofstream file(fileName);

			for (unsigned i = 0; i < Vector::size(); ++i)
				file<<(const std::string &) Vector::operator[](i)<<std::endl;

			file.clear();
			file.close();
		}

		void load()
		{
			try{
				Vector::clear();
				std::ifstream file(fileName);

				if (!file.is_open())
					throw std::logic_error(fileName);

				std::string temp;
				while (std::getline(file, temp))
					Vector::push_back(T(temp));

				file.clear();
				file.close();
			}
			catch(std::logic_error & e){
				std::cerr<<"Loader Error: file "<<e.what()<<" is not found!\n";
				screen::paused();
				exit(EXIT_FAILURE);
			}
		}

		unsigned max_size() const{return MAX_SIZE;}
		bool isFull() const{return MAX_SIZE == Vector::size();}
		int freeSlots() const{return MAX_SIZE - Vector::size();}

		void push_back(const T & x){Vector::push_back(x);}
		void push_back(const Equipment<T> & eq)
		{
			for (unsigned i = 0; i < eq.size(); ++i)
				Vector::push_back(eq[i]);
		}

		void pop_back(){Vector::pop_back();}
		void pop_back(const unsigned & n){Vector::erase(Vector::begin() + n);}

		std::string getFileName() const{return fileName;}
		std::string & getFileName(){return fileName;}

		void show(const unsigned & from = 0) const
		{
			for (unsigned i = 0; i < Vector::size(); ++i)
				showSlot(i, from);
		}

		void showSlot(const unsigned & n, const unsigned & from = 0) const
		{
			std::cout<<n+1+from<<". "<<Vector::operator[](n)<<std::endl;
		}

		void showFreeSlots() const
		{
			std::cout<<"Wolnych miejsc pozostaào: "<<freeSlots()<<std::endl;
		}
		
		int find(const std::string & instance) const
		{
			for (unsigned i = 0; i < Vector::size(); ++i)
			{
				if ((const std::string &) Vector::operator[](i) == instance) 
					return i;
			}
			return -1;
		}
		
		unsigned getAmountOf(const std::string & instance) const
		{
			unsigned amount = 0;
			for (unsigned i = 0; i < Vector::size(); ++i)
			{
				if ((const std::string &) Vector::operator[](i) == instance) 
					++amount;
			}
			return amount;
		}
	};
}
#endif