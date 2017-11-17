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

bool DialogueInterpreter::isWorldAction()
{
    return BasicDialogueInterpreter::isWorldAction(startLine);
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
		if (BasicDialogueInterpreter::isStartState(startLine, start+1)) //Faster EOF
		{
			return true;
		}
        else if (isNpcIssue())
        {
            int n = readNpcIssue();
            if (n == -1) return false;
            else if (n == -2) return true;

            ++state;
        }
        else if (isPlayerIssue())
        {
            if (!readPlayerIssue()) return true; //EOF
        }
		else if (isWorldAction())
		{
			readWorldAction();
		}
    }
    return true;
}

