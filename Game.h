#ifndef GAME_H
#define GAME_H

#include "GameState.h"
#include "StoryManager.h"
#include "Map.h"
#include "MapLoader.h"
#include "Saves.h"
#include "Logs.h"

class Game {
private:
    GameState state;
    StoryManager storyManager;
    Map map;
    MapLoader mapLoader;
    Saves save;
    Logs log;

public:
    Game();
    void saveGame();
    void loadGame();
    void start();
};

#endif

