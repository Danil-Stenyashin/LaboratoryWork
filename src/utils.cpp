#include "include/utils.h"
#include "include/TextProcessor.h"
#include <iostream>

void clearScreen() {
    std::cout << "\033[2J\033[H";
    std::cout.flush();
}

void print(const std::string& text, int delay) {
    TextProcessor::processSpecialCharacters(text, delay);
}

int handleInput(int min, int max) {
    int choice;
    while (true) {
        std::cin >> choice;
        if (std::cin.fail() || choice < min || choice > max) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            print("Некорректный ввод. Попробуйте снова.");
        } else {
            clearScreen();
            return choice;
        }
    }
}
