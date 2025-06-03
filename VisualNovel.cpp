// Danil Stenyashin st128493@student.spbu.ru
// Sunny PUNK



#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <fstream>
#include <functional>
#include <filesystem>
#include <unordered_set> // Для std::unordered_set
#include <unordered_map> // Для std::unordered_map


namespace fs = std::filesystem;

const std::string LOG_FILE = "game/game_log.txt";
const std::string SAVE_FILE = "game/save_data.txt";
const std::string DIALOGUE_FOLDER = "game/dialogues/";
const std::string SAVE_STATES_FILE = "game/save_states.txt";


void clearScreen() {
    std::cout << "\033[2J\033[H";  // ANSI escape-коды для очистки экрана
    std::cout.flush();
}








// Класс персонажа для хранения его характеристик
class Character {
public:

    Character() : name(""), health(100), sanity(100) {}  

    std::string name;
    int health;
    int sanity;

    Character(std::string name, int health = 100, int sanity = 100)
        : name(std::move(name)), health(health), sanity(sanity) {}

    void changeStats(int healthDelta, int sanityDelta) {
        health += healthDelta;
        sanity += sanityDelta;
        if (health < 0) health = 0;
        if (sanity < 0) sanity = 0;
        std::cout << "Статус " << name << ": Здоровье " << health << ", Психика " << sanity << "\n";
    }
};

// Глобальный список персонажей
std::unordered_map<std::string, Character> characters;

// Функция для добавления персонажа в глобальный список
void addCharacter(const std::string& name, int health = 100, int sanity = 100) {
    characters[name] = Character(name, health, sanity);
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
    std::string currentLocation;
    std::unordered_set<std::string> visitedLocations;

public:
    void addLocation(const Location& loc) {
        locations.push_back(loc);
    }
    void setCurrentLocation(const std::string& name) {
        currentLocation = name;
        visitedLocations.insert(name);
    }

    std::string getCurrentLocation() const {
        return currentLocation;
    }

    std::string getLocationDescription(const std::string& name) const {
        for (const auto& loc : locations) {
            if (loc.getName() == name) {
                return loc.getDescription();
            }
        }
        return "Локация не найдена";
    }

    bool isVisited(const std::string& name) const {
        return visitedLocations.count(name) > 0;
    }

    std::vector<std::string> getVisitedLocations() const {
        return {visitedLocations.begin(), visitedLocations.end()};
    }

    void loadState(const std::vector<std::string>& visitedLocs) {
        for (const auto& loc : visitedLocs) {
            visitedLocations.insert(loc);
        }
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
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue; // Пропускаем комментарии

        // Формат: "Название локации|Описание"
        size_t delimiterPos = line.find('|');
        if (delimiterPos == std::string::npos) {
            std::cerr << "Ошибка формата строки: " << line << std::endl;
            continue;
        }

        std::string name = line.substr(0, delimiterPos);
        std::string desc = line.substr(delimiterPos + 1);

        // Удаляем лишние пробелы и кавычки
        name.erase(0, name.find_first_not_of(" \t\""));
        name.erase(name.find_last_not_of(" \t\"") + 1);
        desc.erase(0, desc.find_first_not_of(" \t\""));
        desc.erase(desc.find_last_not_of(" \t\"") + 1);

        gameMap.addLocation(Location(name, desc));
    	}
	}
};

class GameState {
public:
    std::string currentLocation;
    std::vector<std::string> visitedLocations;
    int reputation;  // Репутация игрока
    std::string playerName;  // Имя игрока
    int health;  // Здоровье игрока
    int sanity;  // Состояние психики игрока
    std::vector<std::string> inventory;  // Инвентарь

    void saveToFile(const std::string& filename) {
        std::ofstream file(filename);
        if (file.is_open()) {
            // Сохраняем обычные данные
            file << reputation << "\n" << playerName << "\n" << health << "\n" << sanity << "\n";
            
            // Сохраняем данные карты
            file << currentLocation << "\n";
            file << visitedLocations.size() << "\n";
            for (const auto& loc : visitedLocations) {
                file << loc << "\n";
            }
            
            // Сохраняем инвентарь
            file << inventory.size() << "\n";
            for (const auto& item : inventory) {
                file << item << "\n";
            }
        }
    }

    GameState(int rep = 50, const std::string& name = "Коля", int hp = 100, int sn = 100)
        : reputation(rep), playerName(name), health(hp), sanity(sn) {}



    void loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
   		file >> reputation;
        file.ignore();
        std::getline(file, playerName);
        file >> health >> sanity;
        file.ignore();
        std::getline(file, currentLocation);  // Загружаем локацию
        std::getline(file, playerName);
        file >> health >> sanity;
        size_t itemCount;
        file >> itemCount;
        file.ignore();
        inventory.clear();
        for (size_t i = 0; i < itemCount; ++i) {
            std::string item;
            std::getline(file, item);
            inventory.push_back(item);
            }
        file.close();
        }
    }

};

class GameState; 

class TextProcessor {
private:
    static Map map;
    static GameState* gameState;
    
    static std::string extractLocationName(const std::string& text, size_t start) {
        size_t end = text.find_first_of(" \t\n.,!?", start);
        if (end == std::string::npos) end = text.length();
        std::string location = text.substr(start, end - start);
        // Очистка от лишних пробелов
        location.erase(0, location.find_first_not_of(" \t\n\r"));
        location.erase(location.find_last_not_of(" \t\n\r") + 1);
        // Приведение к верхнему регистру
        std::transform(location.begin(), location.end(), location.begin(), ::toupper);
        return location;
    }

public:

    static Map& getMap() { return map; }
    static const Map& getConstMap() { return map; }

    static std::vector<std::string> getVisitedLocations() {
        return map.getVisitedLocations();
    }
    
    static void loadMapState(const std::vector<std::string>& locations) {
        map.loadState(locations);
    }
    
    static void setCurrentMapLocation(const std::string& location) {
        map.setCurrentLocation(location);
    }

    static void bindGameState(class GameState* state) {
        gameState = state;
    }

    static std::string getCurrentLocation() {
        return map.getCurrentLocation();
    }

    static std::string getCurrentLocationDescription() {
        return map.getLocationDescription(map.getCurrentLocation()); 
    }
    static void setMap(const Map& newMap) {
        map = newMap;  // Публичный метод для установки карты
    }
    static void processSpecialCharacters(const std::string& text, int delay) {
        for (size_t i = 0; i < text.length(); ++i) {
            if (text[i] == '\\' && i + 1 < text.length() && text[i + 1] == 'n') {
                std::this_thread::sleep_for(std::chrono::milliseconds(delay));
                std::cout << "\n";
                ++i;
            } 
            else if (text[i] == '@') {
                std::cout << "\n(Нажмите Enter для продолжения...)";
                std::cin.sync();
                std::cin.ignore();
                std::cin.get();
            } 
            else if (text[i] == '|') {
                std::cin.sync();
                std::cin.get();
                clearScreen();
            } 
            else if (text[i] == '~' && i+1 < text.length() && text[i+1] == 'm') {
                std::string loc = extractLocationName(text, i+2);
                map.setCurrentLocation(loc);
                if (gameState) {
                    gameState->currentLocation = loc; // Сохраняем в GameState
                }
                i += loc.length() + 1;
            }
            else {
                std::cout << text[i] << std::flush;
                if (text[i] != ' ') {
                    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
                }
            }
        }
        std::cout << "\n";
    }
};



Map TextProcessor::map;
GameState* TextProcessor::gameState = nullptr;

void print(const std::string& text, int delay = 30) {
    TextProcessor::processSpecialCharacters(text, delay);
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















class GameState; 



class StoryManager {
private:
    DialogueManager dialogueManager;
    Saves save;
public:
    void startGame() {
        std::string lastDialogue = save.loadProgress();
        dialogueManager.loadDialogue(lastDialogue);
    }
    void newGame() {
    	clearScreen();	
        dialogueManager.loadDialogue("start");
    }
    
};



class Game {
private:
    GameState state;  
    StoryManager storyManager;
    Map gameMap;          // Основная карта игры
    MapLoader mapLoader;  // Загрузчик карт
    Saves save;
    Logs log;

public:
	
    void saveGame() {
    state.currentLocation = TextProcessor::getCurrentLocation();
    state.visitedLocations = TextProcessor::getVisitedLocations(); 
    state.saveToFile(SAVE_FILE);
	}
    

	void loadGame() {
    state.loadFromFile(SAVE_FILE);
    TextProcessor::loadMapState(state.visitedLocations);  // используем публичный метод
    if (!state.currentLocation.empty()) {
        TextProcessor::setCurrentMapLocation(state.currentLocation);  // используем публичный метод
    }
    print("Загрузка выполнена.", 30);
	}

    void showCurrentLocation() {
        std::cout << "┌───────────────────────┐\n"
                  << "│ Текущая локация: \033[1;33m" << state.currentLocation << "\033[0m │\n"
                  << "└───────────────────────┘\n"
                  << TextProcessor::getCurrentLocationDescription() << "\n\n";
    }
    Game() : state(50, "Коля", 100, 100) {
        // Загружаем карту при старте игры
        mapLoader.loadMapFromFile("game/map.txt", gameMap);
        
        // Устанавливаем карту через публичный метод
        TextProcessor::setMap(gameMap);
    }


    void start() {
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
class Player : public Character {
private:
    Inventory inventory;
    Journal journal;

public:
    Player(const std::string& name)
        : Character(name), inventory(), journal() {}

    void addItemToInventory(const Item& item) {
        inventory.addItem(item);
    }

    void addJournalEntry(const std::string& entry) {
        journal.addEntry(entry);
    }

    void showStats() const {
        std::cout << "Игрок: " << name << " | Здоровье: " << health << " | Психика: " << sanity << "\n";
    }
};


int main() {
    clearScreen();
    MainMenu main;
    main.menu();
    return 0;
}
