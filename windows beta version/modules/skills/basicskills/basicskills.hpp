/***
* Author: Stasiek Fortoäski
* Date: 11.07.2017
* Basic Skills System
* Version: 1.0.1
***/

#ifndef BASICSKILLS_HPP_
#define BASICSKILLS_HPP_ 1
#include <array>
#include <iostream>

class BasicSkills
{
public:
    enum{AMOUNT_SKILLS = 4, MAX_LEVEL = 10};

private:
    std::array<std::string, AMOUNT_SKILLS> names;
    std::array<unsigned, AMOUNT_SKILLS> level;
    std::array<double, AMOUNT_SKILLS> power;
    std::array<unsigned, AMOUNT_SKILLS> energyEat;

    void calc();

public:
    BasicSkills(){level.fill(0);}
    BasicSkills(std::array<std::string, AMOUNT_SKILLS> nam,
        std::array<unsigned, AMOUNT_SKILLS> lvl,
        std::array<double, AMOUNT_SKILLS> pow,
        std::array<unsigned, AMOUNT_SKILLS> ene)
        : names(nam), level(lvl), power(pow), energyEat(ene) {calc();}
    virtual ~BasicSkills(){}

    virtual void set(std::array<std::string, AMOUNT_SKILLS> nam,
        std::array<unsigned, AMOUNT_SKILLS> lvl,
        std::array<double, AMOUNT_SKILLS> pow,
        std::array<unsigned, AMOUNT_SKILLS> ene){
            names = nam;
            level = lvl;
            power = pow;
            energyEat = ene;
            calc();
    }

    virtual bool upgrade(const unsigned & n);

    void show() const;
    std::string getRomeLevel(const unsigned & n) const;

    unsigned energyTakes(const unsigned & n) const;

    unsigned getSkillLevel(const unsigned & n) const{return level[n];}
    unsigned & getSkillLevel(const unsigned & n){return level[n];}

    double getSkill(const unsigned & n) const{return power[n];}
    double & getSkill(const unsigned & n){return power[n];}
};
#endif