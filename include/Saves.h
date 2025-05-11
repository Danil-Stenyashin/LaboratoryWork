#ifndef SAVES_H
#define SAVES_H

#include <string>
#include <unordered_map>

class Saves {
public:
    void saveGameState(const std::unordered_map<std::string, std::string>& gameData);
    
    void saveDialogueState(const std::string& dialogueId);
    
    std::unordered_map<std::string, std::string> loadGameState();
    std::string loadDialogueState();

private:
    const std::string SAVE_DIR = "game/saves/";
    const std::string GAME_STATE_FILE = SAVE_DIR + "game_state.dat";
    const std::string DIALOGUE_STATE_FILE = SAVE_DIR + "dialogue_state.dat";
    
    void ensureDirectoryExists() const;
};

#endif
