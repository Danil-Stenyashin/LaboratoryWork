#include "include/MainMenu.h"
#include "include/utils.h"

void MainMenu::menu() {
    while (true) {
        print("---------Главное Меню---------", 0);
        print("(1) Играть\n(2) Посмотреть локацию\n(3) Посмотреть характеристики\n(4) Выйти", 1);
        
        int choice = handleInput(1, 4);
        
        if (choice == 1) {
            clearScreen();
            game.start();
        } else if (choice == 2) {
            clearScreen();
            game.showCurrentLocation();
        } else if (choice == 3) {
            clearScreen();
            print("Имя игрока: " + state.playerName);
            print("Здоровье: " + std::to_string(state.health));
            print("Психическое состояние: " + std::to_string(state.sanity));
            print("Репутация: " + std::to_string(state.reputation));
            print("Инвентарь:");
            for (const std::string& item : state.inventory) {
                print("- " + item);
            }
        } else if (choice == 4) {
            print("Выход из игры...", 40);
            clearScreen();
            std::cout << "Выход из игры";
            print("...", 500);
            clearScreen();
            std::cout << "Выход из игры";
            print("...", 1000);
            exit(0);
        }
    }
}
