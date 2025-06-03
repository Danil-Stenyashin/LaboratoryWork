#ifndef DIALOGUE_MANAGER_H
#define DIALOGUE_MANAGER_H

#include <fstream>
#include <filesystem>
#include <vector> 
#include <string> 
#include "Saves.h"
#include "Logs.h"
#include <string>

class DialogueManager {
private:
    const std::string DIALOGUE_SAVE_PATH = "game/saves/dialogue_progress.txt";
    
    void saveDialogueProgress(const std::string& dialogueId);
    std::string loadDialogueProgress();
    
    Saves save;
    Logs log;
    std::string currentDialogue;
    
public:
    void saveDialogueState(const std::string& dialogueId);
    std::string loadDialogueState();
    void loadDialogue(const std::string& dialogueName);
};

#endif
