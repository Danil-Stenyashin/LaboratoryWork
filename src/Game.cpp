#include "include/Game.h"
#include "include/utils.h"

const std::string PROGRESS_FILE = "game/saves/progress.txt";

Game::Game() : state(50, "Коля", 100, 100) {
    mapLoader.loadMapFromFile("game/map.txt", gameMap);
    TextProcessor::setMap(gameMap);
}

void Game::saveGame() {
    state.currentLocation = TextProcessor::getCurrentLocation();  
    state.visitedLocations = TextProcessor::getVisitedLocations(); 
    state.saveToFile(SAVE_FILE);
}

void Game::loadGame() {
    state.loadFromFile(SAVE_FILE);
    TextProcessor::loadMapState(state.visitedLocations);
    if (!state.currentLocation.empty()) {
        TextProcessor::setCurrentMapLocation(state.currentLocation);
    }
    print("Загрузка выполнена.", 50);
}

void Game::showCurrentLocation() {
    std::cout << "┌───────────────────────┐\n"
              << "│ Текущая локация: \033[1;33m" << state.currentLocation << "\033[0m │\n"
              << "└───────────────────────┘\n"
              << TextProcessor::getCurrentLocationDescription() << "\n\n";
}

void Game::start() {
    log.initializeLogFile();
    
    if (fs::exists(SAVE_FILE) || fs::exists(PROGRESS_FILE)) {
        print("Обнаружено сохранение. Продолжить игру?", 100);
        print("(1) Да\n(2) Нет, начать заново", 100);
        
        int choice = handleInput(1, 2);
        if (choice == 1) {
            loadGame(); 
            
            std::string lastProgress = save.loadProgress();
            if (!lastProgress.empty()) {
                storyManager.setProgress(lastProgress);
            }
            
            clearScreen();
            storyManager.continueGame();
            return;
        }
        else {
            save.deleteAllSaves();
        }
    }
    
    print("Начать новую игру?", 50);
    print("(1) Да\n(2) Выйти в меню", 50);
    
    int choice = handleInput(1, 2);
    if (choice == 1) {
        state.reset(); 
        saveGame(); 
        storyManager.newGame();
    }
}
