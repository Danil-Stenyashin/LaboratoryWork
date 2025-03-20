#include "Game.h"
#include "TextProcessor.h"
#include <iostream>

Game::Game() : state(50, "Коля", 100, 100) {}

void Game::saveGame() {
    state.saveToFile(SAVE_STATES_FILE);
    print("Сохранение выполнено.", 30);
}

void Game::loadGame() {
    state.loadFromFile(SAVE_STATES_FILE);
    print("Загрузка выполнена.", 30);
}

void Game::start() {
    log.initializeLogFile();
    std::string lastProgress = save.loadProgress();

    if (!lastProgress.empty() && lastProgress != "start") {
        print("Обнаружено сохранение: " + lastProgress, 30);
        print("Продолжить с последнего момента?", 30);
        print("(1) Да\n(2) Начать заново", 30);
        int choice = handleInput(1, 2);
        if (choice == 1) {
            print("Продолжение игры...");
            clearScreen();
            storyManager.startGame();
            return;
        }
    }
    print("Вы хотите начать игру?");
    print("(1) Да\n(2) Нет");
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

