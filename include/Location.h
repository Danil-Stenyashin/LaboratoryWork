#ifndef LOCATION_H
#define LOCATION_H

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

#endif
