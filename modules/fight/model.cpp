#include "fight.hpp"

using namespace std;

void Fight::attack(Stats & attacker, Stats & defending) const
{
    if (defending.isDodged()) view->dodge(attacker, defending);
    else if (defending.isBlocked()) view->block(attacker, defending);
    else
    {
        double dmg = attacker.combat();
        defending.hurt(dmg);
        cout<<endl;
        view->damage(attacker, defending, dmg);

        if (defending.isHitbacked())
        {
            view->hitback(defending);

            dmg = defending.getFullDamage();
            attacker.hurt(dmg);
            view->damage(defending, attacker, dmg);
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

unsigned Fight::groupVersusGroup(Group & grp1, Group & grp2) const
{
    grp1.sort();
    grp2.sort();
    for (;;)
    {
        screen::clear();
        cout<<"************* Przegląd **************\n\n\n";
        cout<<"Drużyna 1:\n";
        grp1.show();
        cout<<"\nDrużyna 2:\n";
        grp2.show();
        cout<<endl<<endl<<Color::BG_BLUE<<Color::FG_YELLOW<<"[Dalej]"<<Color::DEFAULT;
        screen::paused();

        for (unsigned i = 0; ; ++i)
        {
            if (i >= grp1.size() && i >= grp2.size()) break;
            else if (i < grp1.size() && i >= grp2.size())
            {
                beforeAttack(i, grp1, grp2);
            }
            else if (i >= grp1.size() && i < grp2.size())
            {
                beforeAttack(i, grp2, grp1);
            }
            else if (grp1[i]->isFaster(*grp2[i]))
            {
                beforeAttack(i, grp1, grp2);
                beforeAttack(i, grp2, grp1);;
            }
            else
            {
                beforeAttack(i, grp2, grp1);
                beforeAttack(i, grp1, grp2);
            }
        }
        grp1.regenerations();
        grp2.regenerations();

        if (grp1.allIsDeath()) return 2;
        else if (grp2.allIsDeath()) return 1;
    }
}
