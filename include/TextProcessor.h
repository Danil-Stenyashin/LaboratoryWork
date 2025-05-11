#ifndef TEXT_PROCESSOR_H
#define TEXT_PROCESSOR_H

#include "Map.h"
#include "GameState.h"
#include <string>
#include <vector>

class TextProcessor {
private:
    static Map map;
    static GameState* gameState;
    
public:
    static void setMap(const Map& newMap);
    static Map& getMap();
    static const Map& getConstMap();
    
    static std::string getCurrentLocation();
    static std::vector<std::string> getVisitedLocations();
    static void loadMapState(const std::vector<std::string>& locations);
    static void setCurrentMapLocation(const std::string& location);
    static std::string getCurrentLocationDescription();
    
    static void bindGameState(GameState* state);
    
    static void processSpecialCharacters(const std::string& text, int delay);
};

#endif
