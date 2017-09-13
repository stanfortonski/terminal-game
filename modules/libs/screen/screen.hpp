/***
* Author: Stasiek Fortoński
* Date: 03.06.2017
* Screen Effects
* Version: 1.1
***/

#ifndef SCREEN_HPP_
#define SCREEN_HPP_ 1
#include <iostream>

namespace screen
{
	enum class Color
	{
		DEFAULT = 0,

		FG_BLACK = 30,
		FG_RED = 31,
		FG_GREEN = 32,
		FG_YELLOW = 33,
		FG_BLUE = 34,
		FG_PURPLE = 35,
		FG_LIGHTBLUE = 36,
		FG_WHITE = 37,

		BG_RESET = 0,
		BG_BLACK = 40,
		BG_RED = 41,
		BG_GREEN = 42,
		BG_YELLOW = 43,
		BG_BLUE = 44,
		BG_PURPLE = 45,
		BG_LIGHTBLUE = 46,
		BG_WHITE = 47,
	};

	inline std::ostream & operator<<(std::ostream & os, const Color & color)
	{
		return os<<"\033["<<(int)color<<";1m";
	}

	inline void clear()
	{
		std::cout<<"\033[2J\033[1;1H";
	}

	inline void paused()
	{
		std::cin.get();
	}
}
#endif
