#include "notes.hpp"

int eq::Notes::learnRecipe(const Item & it)
{
    if (it.getValueType() == TypeItem::RECIPE)
    {
        std::string temp = it.getBuildingComponents()[0];

        for (unsigned i = 0; i < recipes.size(); ++i)
        {
            if (temp == recipes[i])
                return 0;
        }

        recipes.push_back(temp);
        save();
        return 1;
    }
    return -1;
}