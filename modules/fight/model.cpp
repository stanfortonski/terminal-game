#include "fight.hpp"

using namespace std;

void Fight::attack(Stats & attacker, Stats & defending) const
{
    if (defending.isDodged()) view->dodge(attacker, defending);
    else if (defending.isBlocked()) view->block(attacker, defending);
    else
    {
        double dmg = attacker.combat();
        cout<<endl;
        view->damage(attacker, defending, defending.hurt(dmg));

        if (defending.isHitbacked())
        {
            view->hitback(defending);

            dmg = defending.getFullDamage();
            view->damage(defending, attacker, attacker.hurt(dmg));
        }
    }
    screen::paused();
}

void Fight::beforeAttack(const unsigned & n_attacker, Group & attackers, Group & defenders) const
{
    if (!defenders.allIsDeath())
    {
        if (!attackers[n_attacker]->isDead())
            attack(*attackers[n_attacker], *defenders[attackers.target(n_attacker, defenders)]);
    }
}

unsigned Fight::groupVersusGroup(Group & grpa, Group & grpb) const
{
    grpa.sort();
    grpb.sort();
    for (;;)
    {
        screen::clear();
        cout<<"************* Przegl¥d **************\n\n\n";
        cout<<"Dru¾yna 1:\n";
        grpa.show();
        cout<<"\nDru¾yna 2:\n";
        grpb.show();
        cout<<endl<<endl<<Color::YELLOW<<"[Dalej]"<<Color::DEFAULT;
        screen::paused();

        for (unsigned i = 0; ; ++i)
        {
            if (i >= grpa.size() && i >= grpb.size()) break;
            else if (i < grpa.size() && i >= grpb.size())
            {
                beforeAttack(i, grpa, grpb);
            }
            else if (i >= grpa.size() && i < grpb.size())
            {
                beforeAttack(i, grpb, grpa);
            }
            else if (grpa[i]->isFaster(*grpb[i]))
            {
                beforeAttack(i, grpa, grpb);
                beforeAttack(i, grpb, grpa);;
            }
            else
            {
                beforeAttack(i, grpb, grpa);
                beforeAttack(i, grpa, grpb);
            }
        }
        grpa.regenerations();
        grpb.regenerations();

        if (grpa.allIsDeath()) return 2;
        else if (grpb.allIsDeath()) return 1;
    }
}