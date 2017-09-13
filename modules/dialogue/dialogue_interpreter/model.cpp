#include "d_interpreter.hpp"

using namespace std;

bool DialogueInterpreter::isPlayerIssue()
{
    return BasicDialogueInterpreter::isPlayerIssue(startLine, state);
}

bool DialogueInterpreter::isNpcIssue()
{
    return BasicDialogueInterpreter::isNpcIssue(startLine, state);
}

bool DialogueInterpreter::isEnd(const unsigned & endLine)
{
    if (BasicDialogueInterpreter::isEnd(endLine))
    {
        startLine = endLine;
        return true;
    }
    return false;
}

void DialogueInterpreter::startFromLine(const unsigned & start)
{
    for (unsigned i = 1; i <= file.amountOfLines(); ++i)
    {
        if (BasicDialogueInterpreter::isStartState(i, start))
        {
            startLine = i;
            state = 1;
            break;
        }
    }
}

bool DialogueInterpreter::start(const unsigned & start)
{
    startFromLine(start);

    for (; startLine <= file.amountOfLines(); ++startLine)
    {
        if (isNpcIssue())
        {
            int n = readNpcIssue();
            if (n == -1) return false;
            else if (n == -2) return true;

            ++state;
            cout<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Dalej]"<<Color::DEFAULT;
            screen::paused();
        }
        else if (isPlayerIssue())
        {
            readPlayerIssue();
            cout<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Dalej]"<<Color::DEFAULT;
            screen::paused();
        }
    }
    return true;
}

int DialogueInterpreter::readNpcIssue()
{
    for (int i = startLine+1; !isEnd(i); ++i)
    {
        if (BasicDialogueInterpreter::isGetState(i))
        {
            int returnState = getStateNumber(i);
            if (returnState != -1)
                getPlayer().setState(*npc, returnState);
        }
        else if (BasicDialogueInterpreter::isFight(i))
        {
            return -1;
        }
        else if (BasicDialogueInterpreter::isTrade(i))
        {
            for (;;)
            {
                cout<<"Czy chcesz handlować?\n";
                cout<<"1. Tak\n2. Nie\n";
                cout<<"Wybierz działanie: ";
                unsigned choice = setNumber<unsigned>();

                if (choice == 1)
                {
                    Trade::get().control(getPlayer().getInventory(), getPlayer(), npc->getInventory());
                    break;
                }
                else if (choice == 2) break;
            }
        }
        else if (BasicDialogueInterpreter::isGiveItem(i))
        {
            string item_instance = getInstance(i);

            if (!item_instance.empty())
            {
                eq::Equipment<Item> eq;
                Item it(item_instance);
                eq.push_back(it);
                getPlayer().pickItems(eq);
            }
        }
        else if (BasicDialogueInterpreter::isMission(i))
        {
            string mission_instance = getInstance(i);

            if (!mission_instance.empty())
            {
                getPlayer().addMission(BasicMission(mission_instance), getPlayer(), npc->getName());
                cout<<endl<<Color::BG_YELLOW<<Color::FG_BLACK<<"Otrzymałeś nową misję!"<<Color::DEFAULT<<endl;
            }
        }
        else if (BasicDialogueInterpreter::isGrouping(i))
        {
            getGroup().addControl(new NonPlayerCharacter(*npc));
        }
        else if (BasicDialogueInterpreter::isExit(i))
        {
            return -2;
        }
        else
        {
            string str = BasicDialogueInterpreter::file(i);
            if (!str.empty())
            {
                cout<<endl<<Color::FG_GREEN<<npc->getName()<<Color::DEFAULT<<": ";
                message(str+"\n");
            }
        }
    }
    return 0;
}
