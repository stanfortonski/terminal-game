#include "skills.hpp"

using namespace std;

void Skills::set()
{
    switch (getSkillType())
    {
        case DARKNESS:
            BasicSkills::set(
                {"Ci©cie Cienia", "Mroczny Grzmot", "Szelest Cienia", "Furia Mroku"},
                {getSkillLevel(0), getSkillLevel(1), getSkillLevel(2), getSkillLevel(3)},
                {0.1, 0.3, 0.6, 1},
                {0, 14, 24, 36}
            );
        return;

        case LIGHT:
            BasicSkills::set(
                {"Jaskrawy cios", "Bˆysk —wiatˆa", "Sˆoneczna po˜wiata", "Fala —wiatˆa"},
                {getSkillLevel(0), getSkillLevel(1), getSkillLevel(2), getSkillLevel(3)},
                {0.15, 0.2, 0.7, 0.8},
                {0, 10, 22, 32}
            );
        return;

        default:
            BasicSkills::set(
                {"Uderzenie", "Mocne Uderzenie", "Gˆ©bokie Rany", "Ostatnia Szansa"},
                {getSkillLevel(0), getSkillLevel(1), getSkillLevel(2), getSkillLevel(3)},
                {0.16, 0.25, 0.5, 0.7},
                {0, 12, 20, 26}
            );
        return;
    }
}

bool Skills::upgrade(const unsigned & n)
{
    if (BasicSkills::upgrade(n))
    {
        --learnPoints;
        set();
        return true;
    }
    return false;
}

void Skills::upLearnPoints()
{
  if ((anybody->getLevel() % TOUPGRADE) == 0)
    learnPoints += UPDATESKILL;
}

void Skills::save() const
{
    unsigned temp = getSkillType();
    BasicInterpreter::save("skillstypes", temp);

    for (int i = 1; i <= AMOUNT_SKILLS; ++i)
      BasicInterpreter::save("skillpoint["+to_string(i)+"]", getSkillLevel(i-1));

    if (learnPoints != 0)
      BasicInterpreter::save("slp", learnPoints);
}

void Skills::load()
{
    unsigned temp = 0;
    BasicInterpreter::load("skillstypes", temp);
    getSkillType() = Type(temp);

    for (int i = 1; i <= AMOUNT_SKILLS; ++i)
        BasicInterpreter::load("skillpoint["+to_string(i)+"]", getSkillLevel(i-1));

    BasicInterpreter::load("slp", learnPoints);
    set();
}