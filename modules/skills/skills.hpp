/***
* Author: Stasiek Fortoński
* Date: 16.06.2017
* Skills System
* Version: 2
***/

#ifndef SKILLS_HPP_
#define SKILLS_HPP_ 1
#include "skillstype/skillstype.hpp"
#include "basicskills/basicskills.hpp"
#include "../stats/stats.hpp"

class Skills: public BasicSkills, public SkillsType, private BasicInterpreter
{
    unsigned learnPoints = 0;
    Stats * anybody = nullptr;

    virtual bool upgrade(const unsigned & n);
    void set();

public:
    Skills(){}
    explicit Skills(Stats & st): anybody(&st), BasicInterpreter(st.getInstance()){}

    void upLearnPoints();

    virtual void save() const;
    virtual void load();

    void showTreeName() const;
    void showLearnPoints() const;

    void contolerUpgradeSkill();
    void contolerTreeChoser();
};
#endif
