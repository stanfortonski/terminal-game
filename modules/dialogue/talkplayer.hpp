/***
*   Author: Stasiek Fortoński
*   Date: 11.08.17
*   Talk Player System
*   Version: 1
***/

#ifndef TALKPLAYER_HPP
#define TALKPLAYER_HPP 1
#include "../interpreter/basic_interpreter.hpp"
#include "../characters/npc/npc.hpp"

class TalkPlayer: private BasicInterpreter
{
public:
    TalkPlayer(){}
    TalkPlayer(Stats & st): BasicInterpreter(st.getInstance()+"_dialogs"){}

    void setState(const NonPlayerCharacter & npc, const unsigned & state)
    {
        BasicInterpreter::save(npc.getInstance(), state);
    }

    int getState(const NonPlayerCharacter & npc)
    {
        int state = -1;
        ifstream file(getFileName());
        if (file.is_open())
        {
            file.clear();
            file.close();
            BasicInterpreter::load(npc.getInstance(), state);
        }
        return state;
    }
};
#endif