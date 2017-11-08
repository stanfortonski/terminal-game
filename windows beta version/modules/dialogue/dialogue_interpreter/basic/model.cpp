#include "basic.hpp"

using namespace std;

bool BasicDialogueInterpreter::check(const string & command, const unsigned & numberLine, const unsigned & numberOfState)
{
    string str = toLowerCase(trim(file(numberLine)));
    string temp = command + " " + to_string(numberOfState);
    return temp == str;
}

bool BasicDialogueInterpreter::isNpcIssue(const unsigned & numberLine, const unsigned & numberOfState)
{
    return check("!npc:", numberLine, numberOfState);
}

bool BasicDialogueInterpreter::isPlayerIssue(const unsigned & numberLine, const unsigned & numberOfState)
{
    return check("!player:", numberLine, numberOfState);
}

bool BasicDialogueInterpreter::isStartState(const unsigned & numberLine, const unsigned & numberOfState)
{
    return check("!start_state:", numberLine, numberOfState);
}

bool BasicDialogueInterpreter::isWorldAction(const unsigned & numberLine)
{
    string str = toLowerCase(trim(file(numberLine)));
    return str.find("!action:", 0, 8) != string::npos;
}

bool BasicDialogueInterpreter::isEnd(const unsigned & numberLine)
{
    return toLowerCase(trim(file(numberLine))) == "!end";
}

bool BasicDialogueInterpreter::isExit(const unsigned & numberLine)
{
    return toLowerCase(trim(file(numberLine))) == "!exit";
}

bool BasicDialogueInterpreter::isTrade(const unsigned & numberLine)
{
    return toLowerCase(trim(file(numberLine))) == "!trade";
}

bool BasicDialogueInterpreter::isFight(const unsigned & numberLine)
{
    return toLowerCase(trim(file(numberLine))) == "!fight";
}

bool BasicDialogueInterpreter::isGrouping(const unsigned & numberLine)
{
    return toLowerCase(trim(file(numberLine))) == "!group";
}

bool BasicDialogueInterpreter::isGiveItems(const unsigned & numberLine)
{
    string str = toLowerCase(trim(file(numberLine)));
    return str.find("!give_items:", 0, 11) != string::npos;
}

bool BasicDialogueInterpreter::isMission(const unsigned & numberLine)
{
    string str = toLowerCase(trim(file(numberLine)));
    return str.find("!mission:", 0, 9) != string::npos;
}

bool BasicDialogueInterpreter::isGetState(const unsigned & numberLine)
{
    string str = toLowerCase(trim(file(numberLine)));
    return str.find("!get_state:", 0, 11) != string::npos;
}

unsigned BasicDialogueInterpreter::getStateNumber(const unsigned & numberLine)
{
    unsigned numer = 0;
    string str = toLowerCase(trim(file(numberLine)));
    size_t found = str.find_first_of("1234567890");
    if (found != string::npos)
        numer = atoi(str.substr(found, 11).c_str());
    return numer;
}

string BasicDialogueInterpreter::getInstance(const unsigned & numberLine)
{
    string instance;
    string str = toLowerCase(trim(file(numberLine)));
    size_t found = str.find_first_of(":");
    if (found != string::npos)
    {
        str.erase(0, found+2);
        instance = trim(str);
    }
    return instance;
}

vector<string> BasicDialogueInterpreter::getInstances(const unsigned & numberLine)
{
	string str = getInstance(numberLine);
	vector<string> arr;
	
	for (;;)
	{
		size_t found = str.find_first_of(",");
		if (found != string::npos)
		{
			string item = trim(str.substr(0, found));
			if (!item.empty())
				arr.push_back(item);
			str.erase(0, found+2);
		}
		else
		{
			str = trim(str);
			if (!str.empty()) 
				arr.push_back(str);
			break;
		}
	}
	return arr;
}