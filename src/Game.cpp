#include "include/Game.h"
#include "include/utils.h"

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
    std::string lastProgress = save.loadProgress();
    
    if (!lastProgress.empty() && lastProgress != "start") {
        print("Обнаружено сохранение: " + lastProgress, 100);
        print("Продолжить с последнего момента?", 100);
        print("(1) Да\n(2) Начать заново", 100);
        int choice = handleInput(1, 2);
        if (choice == 1) {
            print("Продолжение игры...");
            clearScreen();
            storyManager.startGame();
            return;
        }
    }
    
    print("Вы хотите начать игру?", 50);
    print("(1) Да\n(2) Нет", 50);
    int choice = handleInput(1, 2);
    if (choice == 1) {
        saveGame();
        clearScreen();
        storyManager.newGame();
    } else {
        print("Игра завершена.");
        clearScreen();
        exit(0);
    }
}
