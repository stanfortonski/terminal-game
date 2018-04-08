#include "player.hpp"

void Player::show() const
{
    showLvl();
    Stats::show();
    showExp();
    viewHpForCharacters();
    viewEnergyForCharacters();
}

void Player::showCombat() const
{
    viewHpForCharacters();
    viewEnergyForCharacters();
    std::cout<<std::endl;
    Skills::show();
}
