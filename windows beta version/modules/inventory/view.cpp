#include "inventory.hpp"

using namespace std;

void eq::Inventory::show() const
{
    usedItems.show();
    items.show(AMOUNT_OF_USING_ITEMS);
    items.showFreeSlots();
}