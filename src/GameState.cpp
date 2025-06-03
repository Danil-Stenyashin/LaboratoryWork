#include "include/GameState.h"
#include <fstream>

GameState::GameState(int rep, const std::string& name, int hp, int sn)
    : reputation(rep), playerName(name), health(hp), sanity(sn) {}

void GameState::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << reputation << "\n" << playerName << "\n" << health << "\n" << sanity << "\n";
        file << currentLocation << "\n";
        file << visitedLocations.size() << "\n";
        for (const auto& loc : visitedLocations) {
            file << loc << "\n";
        }
        file << inventory.size() << "\n";
        for (const auto& item : inventory) {
            file << item << "\n";
        }
    }
}


void GameState::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        file >> reputation;
        file.ignore();
        std::getline(file, playerName);
        file >> health >> sanity;
        file.ignore();
        std::getline(file, currentLocation);
        size_t locCount;
        file >> locCount;
        file.ignore();
        visitedLocations.resize(locCount);
        for (size_t i = 0; i < locCount; ++i) {
            std::getline(file, visitedLocations[i]);
        }
        size_t itemCount;
        file >> itemCount;
        file.ignore();
        inventory.clear();
        for (size_t i = 0; i < itemCount; ++i) {
            std::string item;
            std::getline(file, item);
            inventory.push_back(item);
        }
    }
}
