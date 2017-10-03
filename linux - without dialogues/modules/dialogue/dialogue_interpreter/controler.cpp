#include "d_interpreter.hpp"

using namespace std;

void DialogueInterpreter::readPlayerIssue()
{
    unsigned counter = linesToEnd();
    cout<<endl;
    viewPlayerIssueOptions(counter);

    if (counter > 1)
        controlPlayerIssue(counter);
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
    for (unsigned i = 1; i <= amountLine; ++i)
    {
        string str = BasicDialogueInterpreter::file(startLine+i);

        if (amountLine == 1)
        {
            cout<<Color::FG_GREEN<<getPlayer().getName()<<Color::DEFAULT<<": ";
            message(str+"\n");
            break;
        }
        else cout<<i<<". "<<str<<endl;
    }
}

void DialogueInterpreter::controlPlayerIssue(const unsigned & amountLine)
{
    for (;;)
    {
        cout<<"Wybierz kwestie: ";
        unsigned option = setNumber<unsigned>();

        if (option > amountLine) continue;

        for (unsigned i = 1; i <= amountLine; ++i)
        {
            if (option == i)
            {
                cout<<endl<<Color::FG_GREEN<<getPlayer().getName()<<Color::DEFAULT<<": ";
                message(BasicDialogueInterpreter::file(startLine+option)+"\n");
                state = i*100;
                return;
            }
        }
    }
}
