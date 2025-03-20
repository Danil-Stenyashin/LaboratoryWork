#include "Map.h"

Location::Location(const std::string& n, const std::string& desc)
    : name(n), description(desc) {}

std::string Location::getName() const { return name; }
std::string Location::getDescription() const { return description; }

Map::Map() {}

void Map::addLocation(const Location& loc) {
    locations.push_back(loc);
}

void Map::showLocation(const std::string& locationName) {
    for (const Location& loc : locations) {
        if (loc.getName() == locationName) {
            std::cout << "Вы находитесь в " << loc.getName() << std::endl;
            std::cout << loc.getDescription() << std::endl;
            currentLocation = locationName;
            return;
        }
    }
    std::cout << "Локация не найдена!" << std::endl;
}

std::string Map::getCurrentLocation() const {
    return currentLocation;
}

