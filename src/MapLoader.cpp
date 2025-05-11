#include "include/MapLoader.h"
#include <fstream>
#include <iostream>

void MapLoader::loadMapFromFile(const std::string& filename, Map& gameMap) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка при открытии файла карты: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        size_t delimiterPos = line.find('|');
        if (delimiterPos == std::string::npos) {
            std::cerr << "Ошибка формата строки: " << line << std::endl;
            continue;
        }

        std::string name = line.substr(0, delimiterPos);
        std::string desc = line.substr(delimiterPos + 1);

        name.erase(0, name.find_first_not_of(" \t\""));
        name.erase(name.find_last_not_of(" \t\"") + 1);
        desc.erase(0, desc.find_first_not_of(" \t\""));
        desc.erase(desc.find_last_not_of(" \t\"") + 1);

        gameMap.addLocation(Location(name, desc));
    }
}
