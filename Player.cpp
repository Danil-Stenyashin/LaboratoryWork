#include "Player.h"

Player::Player(const std::string& name, int health, int stamina)
    : Character(name, health, stamina) {}

void Player::makeChoice(int choice) {
    std::cout << "Player made choice: " << choice << std::endl;
}

