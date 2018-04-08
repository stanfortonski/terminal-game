/***
*   Author: Stasiek Fortoński
*   Date: 11.08.17
*   Dialogue System
*   Version: 1
***/

#ifndef DIALOGUE_HPP
#define DIALOGUE_HPP 1
#include "dialogue_interpreter/d_interpreter.hpp"

class Dialogue: private DialogueInterpreter
{
public:
    Dialogue(){}
    Dialogue(Group & grp, const unsigned & plr, NonPlayerCharacter & npc)
    : DialogueInterpreter(npc.getInstance()+"_dialogs", grp, plr, npc){}

    bool talk()
    {
        if (DialogueInterpreter::getPlayer().getState(DialogueInterpreter::getNpc()) != -1)
            return DialogueInterpreter::start(DialogueInterpreter::getPlayer().getState(DialogueInterpreter::getNpc()));
        return DialogueInterpreter::start(1);
    }
};
#endif
