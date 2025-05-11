#include "include/StoryManager.h"
#include "include/utils.h"

void StoryManager::startGame() {
    std::string lastDialogue = dialogueManager.loadDialogueState();
    dialogueManager.loadDialogue(lastDialogue);
}


void StoryManager::newGame() {
    clearScreen();
    dialogueManager.loadDialogue("start");
}
