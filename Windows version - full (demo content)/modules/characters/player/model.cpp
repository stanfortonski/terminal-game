#include "player.hpp"

using std::string;

void Player::save()
{
    inventory.save();
    inventory.putall(*this);
    Stats::save();
    Skills::save();
    inventory.load(*this);
    Quests::save();
}

void Player::load()
{
    Stats::load();
    Skills::load();
    Quests::load(*this);
}

void Player::pickItems(const eq::Equipment<Item> & eq)
{
    eq::InventoryController::get().picker(inventory, eq);
    inventory.save();
}