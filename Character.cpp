#include "Character.h"

Character::Character(const std::string& name, int health, int stamina)
    : name(name), health(health), stamina(stamina) {}

std::string Character::getName() const {
    return name;
}

int Character::getHealth() const {
    return health;
}

int Character::getStamina() const {
    return stamina;
}

void Character::setName(const std::string& newName) {
    name = newName;
}

void Character::setHealth(int newHealth) {
    health = newHealth;
}

void Character::setStamina(int newStamina) {
    stamina = newStamina;
}

