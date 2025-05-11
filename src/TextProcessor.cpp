#include "include/TextProcessor.h"
#include "include/GameState.h"
#include <algorithm>
#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>

Map TextProcessor::map;
GameState* TextProcessor::gameState = nullptr;

void TextProcessor::setMap(const Map& newMap) {
    map = newMap;
}

Map& TextProcessor::getMap() {
    return map;
}

const Map& TextProcessor::getConstMap() {
    return map;
}

std::string TextProcessor::getCurrentLocation() {
    return map.getCurrentLocation();
}

std::vector<std::string> TextProcessor::getVisitedLocations() {
    return map.getVisitedLocations();
}

void TextProcessor::loadMapState(const std::vector<std::string>& locations) {
    map.loadState(locations);
}

void TextProcessor::setCurrentMapLocation(const std::string& location) {
    map.setCurrentLocation(location);
    if (gameState) {
        gameState->currentLocation = location;
    }
}

std::string TextProcessor::getCurrentLocationDescription() {
    return map.getLocationDescription(map.getCurrentLocation());
}

void TextProcessor::bindGameState(GameState* state) {
    gameState = state;
}


void TextProcessor::processSpecialCharacters(const std::string& text, int delay) {
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
            std::cout << "\033[2J\033[H" << std::flush;
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
