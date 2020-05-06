/***
* Author: Stasiek Fortoński
* Date: 03.06.2017
* Screen Effects
* Version: 1.2
***/

#ifndef SCREEN_HPP_
#define SCREEN_HPP_ 1
#include <iostream>
#include <windows.h>

namespace screen
{
	enum class Color
	{
		DEFAULT = 0xF,
		BLACK             = 0,
		DARKBLUE          = FOREGROUND_BLUE,
		DARKGREEN         = FOREGROUND_GREEN,
		DARKCYAN          = FOREGROUND_GREEN | FOREGROUND_BLUE,
		DARKRED           = FOREGROUND_RED,
		DARKMAGENTA       = FOREGROUND_RED | FOREGROUND_BLUE,
		DARKYELLOW        = FOREGROUND_RED | FOREGROUND_GREEN,
		DARKGRAY          = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		GRAY              = FOREGROUND_INTENSITY,
		BLUE              = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
		GREEN             = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
		CYAN              = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
		RED               = FOREGROUND_INTENSITY | FOREGROUND_RED,
		MAGENTA           = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
		YELLOW            = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
		WHITE             = 0xF
  };
	
	inline std::ostream & operator<<(std::ostream & os, const Color & color)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (int)color);
		return os;
	}

	inline void clear()
	{
		system("cls");
	}

	inline void paused()
	{
		std::cin.get();
	}
}
#endif