#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <string>
#include <vector>

class GameState {
public:
    
    std::string currentLocation;
    std::vector<std::string> visitedLocations;
    int reputation;
    std::string playerName;
    int health;
    int sanity;
    std::vector<std::string> inventory;

    GameState(int rep = 50, const std::string& name = "Коля", int hp = 100, int sn = 100);
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
    
    void reset() {
    health = 100;
    sanity = 100;
    inventory.clear();
    currentLocation = "start";
    visitedLocations.clear();
    }   
};

#endif
