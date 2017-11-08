#include "battle_view.hpp"
#include "../../libs/screen/screen.hpp"
#include <cmath>

using namespace std;
using namespace screen;

void BattleView::character(const Stats & st) const
{
    cout<<Color::CYAN<<st.getName()<<Color::DEFAULT;
}

void BattleView::damage(const Stats & attacker, const Stats & defending, const double & dmg) const
{
    character(attacker);
    cout<<" zadaje "<<Color::YELLOW<<round(dmg)<<" obra¾eä"<<Color::DEFAULT<<" do ";
    character(defending);
}

void BattleView::dodge(const Stats & attacker, const Stats & defending) const
{
    character(defending);
    cout<<" unika ataku od ";
    character(attacker);
    cout<<endl;
}

void BattleView::block(const Stats & attacker, const Stats & defending) const
{
    character(defending);
    cout<<" blokuje ataku od ";
    character(attacker);
    cout<<endl;
}

void BattleView::hitback(const Stats & st) const
{
    character(st);
    cout<<" kontratakuje!\n";
}