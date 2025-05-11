#include "include/Logs.h"
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;
const std::string LOG_FILE = "game/game_log.txt";

void Logs::initializeLogFile() {
    if (!fs::exists(LOG_FILE)) {
        std::ofstream file(LOG_FILE);
        if (file.is_open()) {
            file << "Лог игры:\n";
            file.close();
        }
    }
}

void Logs::logEvent(const std::string& event) {
    std::ofstream file(LOG_FILE, std::ios::app);
    if (file.is_open()) {
        file << event << "\n";
        file.close();
    }
}
