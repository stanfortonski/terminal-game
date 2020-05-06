#include "basic_mission.hpp"

using namespace std;

string BasicMission::getNameOfMission() const
{
    string name;
    BasicInterpreter::load("name", name);
    return name;
}

std::string BasicMission::getWhoGives() const
{
    string name;
    BasicInterpreter::load("who_gives", name);
    return name;
}

array<string, ORDERS_SIZE> BasicMission::getOrderedItems() const
{
    array<string, ORDERS_SIZE> arr;
    for (unsigned i = 0; i < ORDERS_SIZE; ++i)
    {
        string temp;
        BasicInterpreter::load("item_order["+to_string(i+1)+"]", temp);
        if (!temp.empty()) arr[i] = temp;
    }
    return arr;
}

array<pair<string, unsigned>, ORDERS_SIZE> BasicMission::getOrderedMurders() const
{
    array<pair<string, unsigned>, ORDERS_SIZE> arr;
    for (unsigned i = 0; i < ORDERS_SIZE; ++i)
    {
        string name;
        unsigned amount = 0;

        BasicInterpreter::load("order_murder_name["+to_string(i+1)+"]", name);
        BasicInterpreter::load("order_murder_amount["+to_string(i+1)+"]", amount);

        if (!name.empty())
        {
            arr[i].first = name;
            arr[i].second = amount;
        }
    }
    return arr;
}

Gold BasicMission::getAwardGold() const
{
    unsigned gold = 0;
    BasicInterpreter::load("award_gold", gold);
    return Gold(gold);
}

array<string, ORDERS_SIZE> BasicMission::getAwardItems() const
{
    array<string, ORDERS_SIZE> eq;

    for (unsigned i = 0; i < ORDERS_SIZE; ++i)
    {
        string instance;
        BasicInterpreter::load("award_item["+to_string(i+1)+"]", instance);

        if (!instance.empty())
            eq[i] = instance;
    }
    return eq;
}

unsigned BasicMission::getAwardExp() const
{
    unsigned exp = 0;
    BasicInterpreter::load("award_exp", exp);
    return exp;
}

void BasicMission::setNameOfMission(const string & name) const
{
    BasicInterpreter::save("name", name);
}

void BasicMission::setWhoGives(const string & who) const
{
    BasicInterpreter::save("who_gives", who);
}

void BasicMission::setOrderedItems(const array<string, ORDERS_SIZE> & arr) const
{
    for (unsigned i = 0; i < ORDERS_SIZE; ++i)
    {
        if (!arr[i].empty())
            BasicInterpreter::save("item_order["+to_string(i+1)+"]", arr[i]);
    }
}

void BasicMission::setOrderedMurders(const array<pair<string, unsigned>, ORDERS_SIZE> & arr) const
{
    for (unsigned i = 0; i < ORDERS_SIZE; ++i)
    {
        if (!arr[i].first.empty())
        {
            BasicInterpreter::save("order_murder_name["+to_string(i+1)+"]", arr[i].first);
            BasicInterpreter::save("order_murder_amount["+to_string(i+1)+"]", arr[i].second);
        }
    }
}

void BasicMission::setAwardGold(Gold g) const
{
    int money = g;
    BasicInterpreter::save("award_gold", money);
}

void BasicMission::BasicMission::setAwardItems(const array<string, ORDERS_SIZE> & eq) const
{
    for (unsigned i = 0; i < ORDERS_SIZE; ++i)
    {
        if (!eq[i].empty())
            BasicInterpreter::save("award_item["+to_string(i+1)+"]", eq[i]);
    }
}

void BasicMission::setAwardExp(const unsigned & exp) const
{
    BasicInterpreter::save("award_exp", exp);
}