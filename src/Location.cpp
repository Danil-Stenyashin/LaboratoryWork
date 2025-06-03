#include "include/Location.h"

Location::Location(const std::string& n, const std::string& desc)
    : name(n), description(desc) {}

std::string Location::getName() const { return name; }
std::string Location::getDescription() const { return description; }
