#ifndef MAP_H
#define MAP_H

#include "Location.h"
#include <vector>
#include <string>
#include <unordered_set>

class Map {
private:
    std::vector<Location> locations;
    std::string currentLocation;
    std::unordered_set<std::string> visitedLocations;
    
public:
    void addLocation(const Location& loc);
    void setCurrentLocation(const std::string& name);
    std::string getCurrentLocation() const;
    std::string getLocationDescription(const std::string& name) const;
    bool isVisited(const std::string& name) const;
    std::vector<std::string> getVisitedLocations() const;
    void loadState(const std::vector<std::string>& visitedLocs);
};

#endif
