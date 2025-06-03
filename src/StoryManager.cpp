#include "include/StoryManager.h"
#include "include/utils.h"

void StoryManager::setProgress(const std::string& progress) {
    currentProgress = progress;
    save.saveProgress(progress); 
}

void StoryManager::loadGameState() {
    auto gameState = save.loadGameState();
    
    if (gameState.count("progress")) {
        currentProgress = gameState["progress"];
    }
    
    std::string lastDialogue = save.loadDialogueState();
    if (!lastDialogue.empty()) {
        dialogueManager.loadDialogue(lastDialogue);
    }
}

void StoryManager::continueGame() {
    loadGameState(); 
    
    if (!currentProgress.empty()) {
        dialogueManager.loadDialogue(currentProgress);
    } else {
        newGame(); 
    }
}

void StoryManager::startGame() {
    std::string lastDialogue = save.loadDialogueState();
    if (!lastDialogue.empty()) {
        dialogueManager.loadDialogue(lastDialogue);
    } else {
        newGame();
    }
}

void StoryManager::newGame() {
    clearScreen();
    currentProgress = "start"; 
    save.saveProgress(currentProgress); 
    dialogueManager.loadDialogue(currentProgress);
}
