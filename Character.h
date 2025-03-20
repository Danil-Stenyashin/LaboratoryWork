#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

class Character {
protected:
    std::string name;
    int health;
    int stamina;

public:
    Character(const std::string& name, int health, int stamina);
    
    // Геттеры
    std::string getName() const;
    int getHealth() const;
    int getStamina() const;
    
    // Сеттеры
    void setName(const std::string& newName);
    void setHealth(int newHealth);
    void setStamina(int newStamina);
    
    virtual ~Character() = default;
};

#endif

