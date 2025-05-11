#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"
#include <vector>

class Inventory {
private:
    std::vector<Item> items;
public:
    void addItem(Item item);
};

#endif
