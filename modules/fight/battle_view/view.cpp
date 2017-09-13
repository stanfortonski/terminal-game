#include "battle_view.hpp"
#include "../../libs/screen/screen.hpp"

using namespace std;
using namespace screen;

void BattleView::character(const Stats & st) const
{
    cout<<Color::FG_LIGHTBLUE<<st.getName()<<Color::DEFAULT;
}

void BattleView::damage(const Stats & attacker, const Stats & defending, const double & dmg) const
{
    character(attacker);
    cout<<" zadaje "<<Color::FG_YELLOW<<dmg<<" obrażeń"<<Color::DEFAULT<<" do ";
    character(defending);
    cout<<endl;
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
