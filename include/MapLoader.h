#ifndef MAP_LOADER_H
#define MAP_LOADER_H

#include "Map.h"
#include <string>

class MapLoader {
public:
    void loadMapFromFile(const std::string& filename, Map& gameMap);
};

#endif
