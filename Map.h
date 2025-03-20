#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include <string>

class Location {
private:
    std::string name;
    std::string description;

public:
    Location(const std::string& n, const std::string& desc);
    std::string getName() const;
    std::string getDescription() const;
};

class Map {
private:
    std::vector<Location> locations;
    std::string currentLocation;  

public:
    Map();
    void addLocation(const Location& loc);
    void showLocation(const std::string& locationName);
    std::string getCurrentLocation() const;
};

#endif

