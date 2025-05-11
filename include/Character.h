#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <unordered_map>

class Character {
public:
    std::string name;
    int health;
    int sanity;

    Character();
    Character(std::string name, int health = 100, int sanity = 100);
    void changeStats(int healthDelta, int sanityDelta);
};

extern std::unordered_map<std::string, Character> characters;
void addCharacter(const std::string& name, int health = 100, int sanity = 100);

#endif
