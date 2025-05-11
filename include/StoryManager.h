#ifndef STORY_MANAGER_H
#define STORY_MANAGER_H

#include "DialogueManager.h"
#include "Saves.h"

class StoryManager {
private:
    DialogueManager dialogueManager;
    Saves save;
public:
    void startGame();
    void newGame();
};

#endif
