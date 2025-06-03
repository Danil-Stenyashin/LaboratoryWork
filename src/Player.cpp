#include "include/Player.h"
#include <iostream>

Player::Player(const std::string& name) : Character(name) {}

void Player::addItemToInventory(const Item& item) {
    inventory.addItem(item);
}

void Player::addJournalEntry(const std::string& entry) {
    journal.addEntry(entry);
}

void Player::showStats() const {
    std::cout << "Игрок: " << name << " | Здоровье: " << health 
              << " | Психика: " << sanity << "\n";
}
