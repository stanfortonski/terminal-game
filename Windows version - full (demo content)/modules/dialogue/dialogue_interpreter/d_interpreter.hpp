/***
*   Author: Stasiek Fortoński
*   Date: 2016 - 10.08.17
*   Dialog Interpreter System
*   Version: 3
***/

#ifndef DIALOG_INTERPRETER_HPP
#define DIALOG_INTERPRETER_HPP 1
#include "basic/basic.hpp"
#include "../../libs/screen/screen.hpp"
#include "../../characters/npc/npc.hpp"
#include "../../characters/player/player.hpp"
#include "../../trade/trade.hpp"
#include "../../group/group.hpp"

class DialogueInterpreter: private BasicDialogueInterpreter
{
    Group * grp = nullptr;
    unsigned num_plr = 0;
    NonPlayerCharacter * npc = nullptr;

    unsigned state = 1;
    unsigned startLine = 1;

    bool isPlayerIssue();
	bool isNpcIssue();
	bool isWorldAction();
    bool isEnd(const unsigned & endLine);

	int readNpcIssue();

    bool readPlayerIssue();
    unsigned linesToEnd();
    void viewPlayerIssueOptions(const unsigned & amountLine);
    bool controlPlayerIssue(const unsigned & amountLine);

    void startFromLine(const unsigned & start);
	
	void readWorldAction();

protected:
    Group & getGroup(){
        Group & rgrp = *grp;
        return rgrp;
    }

    Player & getPlayer(){
        return *getGroup().player_cast(getGroup()[num_plr]);
    }

    NonPlayerCharacter & getNpc(){return *npc;}

public:
    DialogueInterpreter(){}
    DialogueInterpreter(const std::string & fn, Group & g, const unsigned & plr, NonPlayerCharacter & n)
    : BasicDialogueInterpreter(fn), grp(&g), num_plr(plr), npc(&n){}

    bool start(const unsigned & start);
};
#endif