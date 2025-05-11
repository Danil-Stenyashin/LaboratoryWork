#ifndef GAME_H
#define GAME_H

#include "GameState.h"
#include "StoryManager.h"
#include "Map.h"
#include "MapLoader.h"
#include "Saves.h"
#include "Logs.h"
#include "TextProcessor.h"

const std::string SAVE_FILE = "game/save_data.txt";
const std::string DIALOGUE_SAVE_PATH = "game/saves/dialogue_progress.txt";

class Game {
private:
    GameState state;
    StoryManager storyManager;
    Map gameMap;
    MapLoader mapLoader;
    Saves save;
    Logs log;

public:
    Game();
    void saveGame();
    void loadGame();
    void showCurrentLocation();
    void start();
};

#endif
