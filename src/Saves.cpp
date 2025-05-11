#include "include/Saves.h"
#include <fstream>
#include <filesystem>
#include <sstream>

namespace fs = std::filesystem;

void Saves::ensureDirectoryExists() const {
    if (!fs::exists(SAVE_DIR)) {
        fs::create_directories(SAVE_DIR);
    }
}

void Saves::saveGameState(const std::unordered_map<std::string, std::string>& gameData) {
    ensureDirectoryExists();
    
    std::ofstream file(GAME_STATE_FILE);
    if (file.is_open()) {
        for (const auto& [key, value] : gameData) {
            file << key << "=" << value << "\n";
        }
    }
}

void Saves::saveDialogueState(const std::string& dialogueId) {
    ensureDirectoryExists();
    
    std::ofstream file(DIALOGUE_STATE_FILE);
    if (file.is_open()) {
        file << dialogueId;
    }
}

std::unordered_map<std::string, std::string> Saves::loadGameState() {
    std::unordered_map<std::string, std::string> gameData;
    
    if (fs::exists(GAME_STATE_FILE)) {
        std::ifstream file(GAME_STATE_FILE);
        std::string line;
        
        while (std::getline(file, line)) {
            size_t delimiter = line.find('=');
            if (delimiter != std::string::npos) {
                std::string key = line.substr(0, delimiter);
                std::string value = line.substr(delimiter + 1);
                gameData[key] = value;
            }
        }
    }
    
    return gameData;
}

std::string Saves::loadDialogueState() {
    if (fs::exists(DIALOGUE_STATE_FILE)) {
        std::ifstream file(DIALOGUE_STATE_FILE);
        std::string dialogueId;
        std::getline(file, dialogueId);
        return dialogueId;
    }
    return "start";
}
