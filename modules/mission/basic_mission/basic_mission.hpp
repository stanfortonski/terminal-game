/***
*   Author: Stasiek Fortoński
*   Date: 13.08.17
*   Basic Mission
*   Version: 1
***/

#ifndef BASICMISSION_HPP
#define BASICMISSION_HPP 1
#include <iostream>
#include <utility>
#include "../../interpreter/basic_interpreter.hpp"
#include "../../stats/stats.hpp"
#include "../../inventory/inventory.hpp"

const unsigned ORDERS_SIZE = 6;

class BasicMission: protected BasicInterpreter
{
protected:
    void setNameOfMission(const std::string & name) const;
    void setWhoGives(const std::string & who) const;
    void setOrderedItems(const std::array<std::string, ORDERS_SIZE> & arr) const;
    void setOrderedMurders(const std::array<std::pair<std::string, unsigned>, ORDERS_SIZE> & arr) const;
    void setAwardGold(Gold g) const;
    void setAwardItems(const std::array<std::string, ORDERS_SIZE> & eq) const;
    void setAwardExp(const unsigned & exp) const;

public:
    BasicMission(){}
    explicit BasicMission(const std::string & fn): BasicInterpreter("missions/"+fn){}

    std::string getNameOfMission() const;
    std::string getWhoGives() const;
    std::array<std::string, ORDERS_SIZE> getOrderedItems() const;
    std::array<std::pair<std::string, unsigned>, ORDERS_SIZE> getOrderedMurders() const;
    Gold getAwardGold() const;
    std::array<std::string, ORDERS_SIZE> getAwardItems() const;
    unsigned getAwardExp() const;
};
#endif
