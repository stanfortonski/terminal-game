#include "d_interpreter.hpp"

using namespace std;

bool DialogueInterpreter::readPlayerIssue()
{
    unsigned counter = linesToEnd();
	cout<<endl;
	
    if (counter > 1)
	{
        if (!controlPlayerIssue(counter))
			return false;
	}
	else {
		viewPlayerIssueOptions(counter);
		cout<<Color::YELLOW<<"[Dalej]"<<Color::DEFAULT;
        screen::paused();
	}
	return true;
}

unsigned DialogueInterpreter::linesToEnd()
{
    unsigned counter = 0;
    while (!isEnd(startLine+1+counter))
    {
        string temp = BasicDialogueInterpreter::file(startLine+1+counter);
        ++counter;
    }
    startLine -= counter+1;
    return counter;
}

void DialogueInterpreter::viewPlayerIssueOptions(const unsigned & amountLine)
{
	unsigned i = 1;
    for (; i <= amountLine; ++i)
    {
        string str = BasicDialogueInterpreter::file(startLine+i);

        if (amountLine == 1)
        {
            cout<<Color::GREEN<<getPlayer().getName()<<Color::DEFAULT<<": ";
            message(str+"\n");
            break;
        }
        else cout<<i<<". "<<str<<endl;
    }
	
	if (amountLine > 1)
		cout<<i<<". koniec\n";
}

bool DialogueInterpreter::controlPlayerIssue(const unsigned & amountLine)
{
    for (;;)
    {
		viewPlayerIssueOptions(amountLine);
        cout<<"Wybierz kwestie: ";
        unsigned option = setNumber<unsigned>();

		if (option == amountLine+1) return false;
        else if (option > amountLine) 
		{
			screen::clear();
			continue;
		}

        for (unsigned i = 1; i <= amountLine; ++i)
        {
            if (option == i)
            {
                cout<<endl<<Color::GREEN<<getPlayer().getName()<<Color::DEFAULT<<": ";
                message(BasicDialogueInterpreter::file(startLine+option)+"\n");
                state = i*100;
                return true;
            }
        }
    }
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
			
			return 0;
        }
        else if (BasicDialogueInterpreter::isFight(i))
        {
            return -1;
        }
        else if (BasicDialogueInterpreter::isTrade(i))
        {
            for (;;)
            {
                cout<<"\nCzy chcesz handlowa†?\n";
                cout<<"1. Tak\n2. Nie\n";
                cout<<"Wybierz dziaˆanie: ";
                unsigned choice = setNumber<unsigned>();

                if (choice == 1)
                {
                    Trade::get().control(getPlayer().getInventory(), getPlayer(), npc->getInventory());
                    return 0;
                }
                else if (choice == 2) return 0;
            }
        }
        else if (BasicDialogueInterpreter::isGiveItems(i))
        {
            vector<string> item_instances = getInstances(i);
			eq::Equipment<Item> eq;
			
			for (unsigned i = 0; i < item_instances.size(); ++i)
			{
				if (!item_instances[i].empty())
				{
					eq.push_back(Item(item_instances[i]));
				}
			}
			getPlayer().pickItems(eq);
			return 0;
        }
        else if (BasicDialogueInterpreter::isMission(i))
        {
            vector<string> mission_instances = getInstances(i);

			for (unsigned i = 0; i < mission_instances.size(); ++i)
			{
				if (!mission_instances[i].empty())
				{
					getPlayer().addMission(BasicMission(mission_instances[i]), getPlayer(), getNpc().getInstance());
				}
			}
			
			if (mission_instances.size() > 1)
			{
				cout<<endl<<Color::YELLOW<<"Otrzymaˆe˜ "<<mission_instances.size()<<" nowe misje!"<<Color::DEFAULT<<endl;
			}
			else cout<<endl<<Color::YELLOW<<"Otrzymaˆe˜ now¥ misj©!"<<Color::DEFAULT<<endl;
			
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
                cout<<endl<<Color::GREEN<<npc->getName()<<Color::DEFAULT<<": ";
                message(str+"\n");
            }
			else return 0;
        }
    }
	cout<<Color::YELLOW<<"[Dalej]"<<Color::DEFAULT;
    screen::paused();
    return 0;
}

void DialogueInterpreter::readWorldAction()
{
	for (int i = startLine+1; !isEnd(i); ++i)
	{
		string str = BasicDialogueInterpreter::file(i);
        if (!str.empty())
        {
            cout<<endl<<Color::CYAN<<"<< "+str+" >>\n"<<Color::DEFAULT;
        }
	}
	cout<<Color::YELLOW<<"[Dalej]"<<Color::DEFAULT;
    screen::paused();
}