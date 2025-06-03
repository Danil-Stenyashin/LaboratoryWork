#ifndef STORY_MANAGER_H
#define STORY_MANAGER_H

#include "DialogueManager.h"
#include "Saves.h"
#include <string>

class StoryManager {
private:
    DialogueManager dialogueManager;
    Saves save;
    std::string currentProgress; 
    
public:
    void startGame();
    void newGame();
    void setProgress(const std::string& progress);
    void continueGame();
    void loadGameState(); 
};

#endif
