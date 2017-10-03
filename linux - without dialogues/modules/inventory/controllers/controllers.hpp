#ifndef EQ_CONTROLLERS
#define EQ_CONTROLLERS 1
#include "../inventory.hpp"

namespace eq
{
    class BasicController
    {
    public:
        virtual void control(Inventory & inv){};
    };


    class InventoryController: public BasicController
    {
    protected:
        InventoryController(){}

        void selected(Inventory & inv, Stats & st, const unsigned & n);
        void showOption(Inventory & inv, Stats & st, const unsigned & n);
        bool learningView(Inventory & inv, const unsigned & n);
        void selectedUsed(Inventory & inv, Stats & st, const unsigned & n);
        void chooseWasPick(Inventory & inv, const Equipment<Item> & adds);

    public:
        static InventoryController & get()
        {
            static InventoryController instance;
            return instance;
        }

        virtual void control(Inventory & inv, Stats & st);
        void picker(Inventory & inv, const Equipment<Item> & adds);
    };
}
#endif
