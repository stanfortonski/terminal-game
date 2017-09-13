#ifndef BATTLEVIEW_HPP
#define BATTLEVIEW_HPP 1
#include <iostream>
#include "../../stats/stats.hpp"

class BasicBattleView
{
public:
    virtual void character(const Stats & st) const{};
    virtual void damage(const Stats & attacker, const Stats & defending, const double & dmg) const{};
    virtual void dodge(const Stats & attacker, const Stats & defending) const{};
    virtual void block(const Stats & attacker, const Stats & defending) const{};
    virtual void hitback(const Stats & st) const{};
};

class BattleView: public BasicBattleView
{
protected:
    BattleView(){}
public:
    static BattleView & get()
    {
        static BattleView instance;
        return instance;
    }

    virtual void character(const Stats & st) const;
    virtual void damage(const Stats & attacker, const Stats & defending, const double & dmg) const;
    virtual void dodge(const Stats & attacker, const Stats & defending) const;
    virtual void block(const Stats & attacker, const Stats & defending) const;
    virtual void hitback(const Stats & st) const;
};
#endif
