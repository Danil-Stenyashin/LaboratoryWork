#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Inventory.h"
#include "Journal.h"
#include <string>

class Player : public Character {
private:
    Inventory inventory;
    Journal journal;
public:
    Player(const std::string& name);
    void addItemToInventory(const Item& item);
    void addJournalEntry(const std::string& entry);
    void showStats() const;
};

#endif
