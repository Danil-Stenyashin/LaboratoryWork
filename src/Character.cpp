#include "include/Character.h"
#include <iostream>
#include <algorithm>

std::unordered_map<std::string, Character> characters;

Character::Character() : name(""), health(100), sanity(100) {}

Character::Character(std::string name, int health, int sanity)
    : name(std::move(name)), health(health), sanity(sanity) {}

void Character::changeStats(int healthDelta, int sanityDelta) {
    health += healthDelta;
    sanity += sanityDelta;
    if (health < 0) health = 0;
    if (sanity < 0) sanity = 0;
    std::cout << "Статус " << name << ": Здоровье " << health << ", Психика " << sanity << "\n";
}

void addCharacter(const std::string& name, int health, int sanity) {
    characters[name] = Character(name, health, sanity);
}
