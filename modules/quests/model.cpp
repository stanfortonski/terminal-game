#include "quests.hpp"

using namespace std;

void Quests::load(Stats & st)
{
    missions.load();
    if (missions.size() == 0)
    {
        if (system(string("rm -r "+PLAYER_DIR+st.getName()+"/missions").c_str()) != -1)
        {
            if (system(string("mkdir -p "+PLAYER_DIR+st.getName()+"/missions").c_str()) != -1);
        }
    }
}

void Quests::save() const
{
    missions.save();
}

void Quests::addMission(const BasicMission & bs, Stats & st, const std::string & who)
{
    missions.push_back(Mission(bs, st, who));
    missions.save();
}

void Quests::isTargetKilled(const Stats & st)
{
    for (unsigned i = 0; i < missions.size(); ++i)
    {
        missions[i].isTargetKilled(st);
    }
}
