#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
private:
    std::string name;
public:
    Item(std::string n);
    std::string getName();
};

#endif
