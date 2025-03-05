#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <fstream>
#include <functional>
#include <filesystem>

namespace fs = std::filesystem;

const std::string LOG_FILE = "game/game_log.txt";
const std::string SAVE_FILE = "game/save_data.txt";
const std::string DIALOGUE_FOLDER = "game/dialogues/";
const std::string SAVE_STATES_FILE = "game/save_states.txt";


void clearScreen() {
    std::cout << "\033[2J\033[H";  // ANSI escape-коды для очистки экрана
    std::cout.flush();
}







class Location {
private:
    std::string name;
    std::string description;

public:
    Location(const std::string& n, const std::string& desc)
        : name(n), description(desc) {}

    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
};







class Map {
private:
    std::vector<Location> locations;
    std::string currentLocation;  // Храним текущую локацию

public:
    void addLocation(const Location& loc) {
        locations.push_back(loc);
    }

    void showLocation(const std::string& locationName) {
        for (const Location& loc : locations) {
            if (loc.getName() == locationName) {
                std::cout << "Вы находитесь в " << loc.getName() << std::endl;
                std::cout << loc.getDescription() << std::endl;
                currentLocation = locationName;  // Запоминаем текущую локацию
                return;
            }
        }
        std::cout << "Локация не найдена!" << std::endl;
    }

    std::string getCurrentLocation() const {
        return currentLocation;
    }
};


class MapLoader {
public:
    void loadMapFromFile(const std::string& filename, Map& gameMap) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Ошибка при открытии файла карты: " << filename << std::endl;
            return;
        }

        std::string line;
        bool readingLocations = false;

        while (std::getline(file, line)) {
            if (line.empty()) continue;

            if (line == "# Локации") {
                readingLocations = true;
                continue;
            }

            if (readingLocations) {
                // Читаем локации и их описания
                std::string locationName = line;
                // Удаляем кавычки, если они есть
                if (locationName.front() == '"') locationName.erase(locationName.begin());
                if (locationName.back() == '"') locationName.pop_back();
                std::getline(file, line);
                Location newLocation(locationName, line);
                gameMap.addLocation(newLocation);
            }
        }
    }
};



void print(const std::string& text, int delay = 30) {
    Map map;
    MapLoader mapLoader;
    mapLoader.loadMapFromFile("game/map.txt", map); // Указывать строго в родительном падеже!
    for (size_t i = 0; i < text.length(); ++i) {
        if (text[i] == '\\' && i + 1 < text.length() && text[i + 1] == 'n') {
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
            std::cout << std::endl;
            ++i;
        } else if (text[i] == '@') { // Специальный символ для паузы
            std::cout << std::endl << "(Нажмите Enter для продолжения...)";
            std::cin.sync();
            std::cin.ignore();
            std::cin.get();
            clearScreen();
        } else if (text[i] == '|') { // Специальный символ для паузы без подсказки
            std::cin.sync();
            std::cin.get();
            clearScreen();
        } else if (text[i] == '~' && i + 1 < text.length() && text[i + 1] == 'm') { // Проверяем ~mНазвание
            size_t startPos = i + 2;  // Начинаем сразу после ~m
            size_t endPos = text.find(' ', startPos);  // Ищем первый пробел

            // Если пробела нет, используем всю строку до конца
            if (endPos == std::string::npos) {
                endPos = text.length();
            }

            std::string location = text.substr(startPos, endPos - startPos);
            std::transform(location.begin(), location.end(), location.begin(), ::toupper);  // Преобразуем в верхний регистр
            map.showLocation(location);  
            i = endPos - 1; 
            continue;
        } else {
            std::cout << text[i] << std::flush;
            if (text[i] != ' ') {
                std::this_thread::sleep_for(std::chrono::milliseconds(delay));
            }
        }
    }
    std::cout << std::endl;
}







class Logs {
public:
	void initializeLogFile() {
	    if (!fs::exists(LOG_FILE)) {
		std::ofstream file(LOG_FILE);
		if (file.is_open()) {
		    file << "Лог игры:\n";
		    file.close();
		}
	    }
	}


	void logEvent(const std::string& event) {
	    std::ofstream file(LOG_FILE, std::ios::app);
	    if (file.is_open()) {
		file << event << "\n";
		file.close();
	    }
	}
};





class Saves {
public:
	// Функция для сохранения текущего состояния игры
	void saveProgress(const std::string& state) {
	    std::ofstream file(SAVE_FILE);
	    if (file.is_open()) {
		file << state << "\n";
		file.close();
	    }
	}


	// Функция для загрузки сохраненного состояния
	std::string loadProgress() {
	    if (fs::exists(SAVE_FILE)) {
		std::ifstream file(SAVE_FILE);
		std::string state;
		if (file.is_open()) {
		    std::getline(file, state);
		    file.close();
		    return state;
		}
	    }
	    return "start"; // Начинать с "start", если сохранения нет
	}
};

// Функция для обработки пользовательского ввода
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





class DialogueManager {
private:
    Saves save;
    Logs log;
public:
    void loadDialogue(const std::string& dialogueName) {

        std::string filePath = DIALOGUE_FOLDER + dialogueName + ".txt";

        if (!fs::exists(filePath)) {
            std::cout << "Ошибка: диалог " << dialogueName << " не найден." << std::endl;
            return;
        }

        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cout << "Ошибка: не удалось загрузить диалог " << dialogueName << std::endl;
            return;
        }

        std::string line;
        std::vector<std::string> choices;
        int textSpeed = 30; // Скорость по умолчанию

        while (std::getline(file, line)) {
            if (line.rfind("speed=", 0) == 0) {
                textSpeed = std::stoi(line.substr(6));
                continue;
            }
            if (line.rfind("#", 0) == 0) {
                break;
            }
            print(line, textSpeed);
        }

        while (std::getline(file, line)) {
            if (line.rfind("#", 0) == 0) {  // Если строка начинается с "#", то это конец диалога
                break;
            }
            choices.push_back(line);
        }

        for (size_t i = 0; i < choices.size(); ++i) {
            std::string choiceText = choices[i].substr(5); // Срезаем первые 5 символов
            std::cout << "(" << std::to_string(i + 1) + ") " + choiceText << std::endl;
        }

        int choice = handleInput(1, choices.size());
        log.logEvent("Выбран вариант: " + choices[choice - 1].substr(5));
        save.saveProgress(choices[choice - 1].substr(0, 5));
        
        loadDialogue(choices[choice - 1].substr(0, 5));
    }
};





class Character {
protected:
    std::string name;
public:
    Character(std::string n) : name(n) {}
    virtual void speak() = 0;
    std::string getName() { return name; }
};




class Heroine : public Character {
public:
    Heroine(std::string n) : Character(n) {}
    void speak() override {
        print(name + ": Привет, Коля. Ты ведь тоже не знаешь, как здесь оказался?");
    }
};


















class Player {
private:
    std::string name;
public:
    Player(std::string n) : name(n) {}
    std::string getName() { return name; }
};













class Scene {
private:
    std::vector<std::string> description;
public:
    Scene(const std::vector<std::string>& desc) : description(desc) {}
    void showScene() {
        for (const std::string& line : description) {
            print(line);
        }
    }
};






















class Choice {
private:
    std::string text;
    int consequence;
public:
    Choice(std::string t, int c) : text(t), consequence(c) {}
    int makeChoice() {
        print("Выбор: " + text);
        return consequence;
    }
};




class Item {
private:
    std::string name;
public:
    Item(std::string n) : name(n) {}
    std::string getName() { return name; }
};




class Inventory {
private:
    std::vector<Item> items;
public:
    void addItem(Item item) { items.push_back(item); }
};




class Journal {
private:
    std::vector<std::string> entries;
public:
    void addEntry(std::string entry) { entries.push_back(entry); }
};





class State {
protected:
    int value;
public:
    State(int v) : value(v) {}
    int getValue() { return value; }
};




class Health : public State {
public:
    Health(int v) : State(v) {}
};




class Sanity : public State {
public:
    Sanity(int v) : State(v) {}
};




class Emotion {
private:
    std::string type;
public:
    Emotion(std::string t) : type(t) {}
};




class AI {
private:
    Emotion emotion;
public:
    AI(std::string e) : emotion(e) {}
};













class GameState {
public:
    int reputation;  // Репутация игрока
    std::string playerName;  // Имя игрока
    int health;  // Здоровье игрока
    int sanity;  // Состояние психики игрока
    std::vector<std::string> inventory;  // Инвентарь

    GameState(int rep = 50, const std::string& name = "Коля", int hp = 100, int sn = 100)
        : reputation(rep), playerName(name), health(hp), sanity(sn) {}


    void saveToFile(const std::string& filename) {
        std::ofstream file(filename);
        if (file.is_open()) {
            file << reputation << std::endl;
            file << playerName << std::endl;
            file << health << std::endl;
            file << sanity << std::endl;
            file << inventory.size() << std::endl;  // Количество предметов в инвентаре
            for (const std::string& item : inventory) {
                file << item << std::endl;
            }
            file.close();
        }
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            file >> reputation;
            file.ignore();  // Пропускаем символ новой строки после числа
            std::getline(file, playerName);
            file >> health;
            file >> sanity;
            size_t inventorySize;
            file >> inventorySize;
            file.ignore();  // Пропускаем символ новой строки после числа
            inventory.clear();
            for (size_t i = 0; i < inventorySize; ++i) {
                std::string item;
                std::getline(file, item);
                inventory.push_back(item);
            }
            file.close();
        }
    }
};




class StoryManager {
private:
    std::vector<Heroine> heroines;
    DialogueManager dialogueManager;
    Saves save;
public:
    StoryManager() {
        heroines.push_back(Heroine("Алиса"));
        heroines.push_back(Heroine("Лена"));
        heroines.push_back(Heroine("Арслан"));
    }
    void startGame() {
        std::string lastDialogue = save.loadProgress();
        dialogueManager.loadDialogue(lastDialogue);
    }
    void newGame() {
        dialogueManager.loadDialogue("start");
    }
    
};



class Game {
private:
    Player* player;
    GameState state;  
    StoryManager storyManager;
    Map map;
    MapLoader mapLoader;
    Saves save;
    Logs log;
public:
    void saveGame() {
        state.saveToFile(SAVE_STATES_FILE);  // Сохраняем состояние в файл
        print("Сохранение выполнено.", 30);
    }

    void loadGame() {
        state.loadFromFile(SAVE_STATES_FILE);  // Загружаем состояние из файла
        print("Загрузка выполнена.", 30);
    }
    
    Game() : state() {} 
    void start() {
         
        log.initializeLogFile();
        std::string lastProgress = save.loadProgress();
        

        
        if (!lastProgress.empty() && lastProgress != "start") {
            print("Обнаружено сохранение: " + lastProgress,30);
            print("Продолжить с последнего момента?",30);
            print("(1) Да\n(2) Начать заново",30);
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
};




class MainMenu {
private:
    Game game;    
    Map map;
    GameState state;
    MapLoader mapLoader;
    
public:
    void menu() {
    
    while (true) {    
	    
	    print("---------Главное Меню---------",0);
	    print("(1) Играть\n(2) Посмотреть локацию\n(3) Посмотреть характеристики\n(4) Выйти",1);
	    
	    
	    int choice = handleInput(1, 4);
	    
	    
	    if (choice == 1) {
		clearScreen();
		game.start();
		       
	    } else if (choice == 2) {
		clearScreen();
		print("Текущая локация: " + map.getCurrentLocation());  
	    
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
                print("Выход из игры...",40);
                clearScreen();
                std::cout << "Выход из игры";
                print("...",500);
                clearScreen();
                std::cout << "Выход из игры";
                print("...",1000);
	        exit(0);
	    
	    }   
    }  
    }
};




int main() {
    clearScreen();
    MainMenu main;
    main.menu();
    return 0;
}

