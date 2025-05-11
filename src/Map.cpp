#include "include/Map.h"

void Map::addLocation(const Location& loc) {
    locations.push_back(loc);
}

void Map::setCurrentLocation(const std::string& name) {
    currentLocation = name;
    visitedLocations.insert(name);
}

std::string Map::getCurrentLocation() const {
    return currentLocation;
}

std::string Map::getLocationDescription(const std::string& name) const {
    for (const auto& loc : locations) {
        if (loc.getName() == name) {
            return loc.getDescription();
        }
    }
    return "Локация не найдена";
}

bool Map::isVisited(const std::string& name) const {
    return visitedLocations.count(name) > 0;
}

std::vector<std::string> Map::getVisitedLocations() const {
    return {visitedLocations.begin(), visitedLocations.end()};
}

void Map::loadState(const std::vector<std::string>& visitedLocs) {
    for (const auto& loc : visitedLocs) {
        visitedLocations.insert(loc);
    }
}
