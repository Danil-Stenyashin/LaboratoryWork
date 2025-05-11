#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "Game.h"
#include "Map.h"
#include "GameState.h"
#include "MapLoader.h"

class MainMenu {
private:
    Game game;
    Map map;
    GameState state;
    MapLoader mapLoader;
public:
    void menu();
};

#endif
