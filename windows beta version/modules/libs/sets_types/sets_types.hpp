//SETSBASICTYPES_HPP_ for linux = 1
//SETSBASICTYPES_HPP_ for windows = 2

#ifndef SETSBASICTYPES_HPP_
#define SETSBASICTYPES_HPP_ 2
#include <iostream>
#include <cctype>
#include <ctime>

#if SETSBASICTYPES_HPP_ == 1
#include <unistd.h>
#elif SETSBASICTYPES_HPP_ == 2
#include <windows.h>
#endif

using namespace std;

template <class T>
inline T setNumber()
{
	T temp;
	while (!(cin>>temp))
	{
		cin.clear();
		cin.ignore();
	}

	cin.clear();
	cin.ignore();
	return temp;
}

inline string setString()
{
	string str;
	while (!getline(cin, str))
	{
		cin.clear();
		cin.ignore();
	}
	return str;
}

inline string toLowerCase(string str)
{
	for (int i = 0; str[i]; ++i)
		str[i] = tolower(str[i]);
  return str;
}

inline string toUpperCase(string str)
{
	for (int i = 0; str[i]; ++i)
		str[i] = toupper(str[i]);
  return str;
}

inline string newLine(string str)
{
    string toFind = "\\n";
    size_t found;
    bool isFind = false;
    while (isFind == false)
    {
        if ((found = str.find(toFind)) != string::npos)
        {
            str = str.erase(found, toFind.size());
            str = str.insert(found, "\n");
            continue;
        }
        isFind = true;
    }
    return str;
}

inline void wait(const double & sec)
{
	for (clock_t start = clock() + sec * CLOCKS_PER_SEC; start > clock();)
		continue;
}

inline void message(const string & str, const unsigned & milisec=80)
{
    for (unsigned i = 0; str[i]; ++i)
    {
		#if SETSBASICTYPES_HPP_ == 1
			if (str[i] != ' ') usleep(milisec*1000);
		#elif SETSBASICTYPES_HPP_ == 2
        	if (str[i] != ' ') Sleep(milisec);
		#endif

        cout<<str[i];
    }
}

inline string reverse(const string & line)
{
    string str;
    for (int i = line.size()-1; i >= 0 ; --i)
        str += line[i];
    return str;
}

inline string ltrim(const string & line)
{
    if (line.empty()) return line;
	string str = line;
    size_t foundFirstChar = str.find_first_not_of(" \\t");

    if (foundFirstChar != string::npos)
        str.erase(0, foundFirstChar);
	return str;
}

inline string rtrim(const string & line)
{
    if (line.empty()) return line;

	string str = line;
    size_t foundLastChar = str.find_last_not_of(" \\t");

    if (foundLastChar != string::npos)
        str.erase(foundLastChar+1, str.size()-foundLastChar);
	return str;
}

inline string trim(const string & line)
{
    string str = ltrim(line);
    str = rtrim(str);
	return str;
}
#endif