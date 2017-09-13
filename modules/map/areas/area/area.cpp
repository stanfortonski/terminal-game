#include "area.hpp"

using namespace std;

void _map::Area::setWay(Area & ptr)
{
    if ((amount != MAX_PLACES) && (ptr.amount != MAX_PLACES))
    {
        places[amount++] = &ptr;
        ptr.places[ptr.amount++] = this;
    }
}

_map::Area & _map::Area::getPlace(const int & n) const
{
    return *places[n];
}

unsigned _map::Area::getId() const
{
    unsigned temp = 0;
    BasicInterpreter::load("id", temp);
    return temp;
}

string _map::Area::getName() const
{
    string name;
    BasicInterpreter::load("name", name);
    return name;
}

string _map::Area::getDescription() const
{
    string desc;
    BasicInterpreter::load("description", desc);
    return newLine(desc);
}

vector<string> _map::Area::getInstanceOfNpcs() const
{
    vector<string> npcs;
    for (unsigned i = 0; i < MAX_PLACES; ++i)
    {
        string temp;
        BasicInterpreter::load("npc[" + to_string(i+1) + "]", temp);
        if (!temp.empty()) npcs.push_back(temp);
    }
    return npcs;
}

unsigned _map::Area::getMinimalLVL() const
{
    unsigned min = 0;
    BasicInterpreter::load("minlvl", min);
    return min;
}
