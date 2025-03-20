#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <iostream>

class Player : public Character {
public:
    Player(const std::string& name, int health = 100, int stamina = 100);

    void makeChoice(int choice);
};

#endif

