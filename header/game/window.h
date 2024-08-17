#pragma once 
#include "../header/battle/utility.h"
#include "../header/game/battle.h"
#include "../header/game/kingdom.h"

class Screen {
private: 
    std::unique_ptr<sf::RenderWindow> window; 
    sf::Event event; 

    BattleState battle; 
    KingdomState kingdom;  
public: 
    Screen(); 

    void handleEvents(); 
    void update(); 
    void render();
    bool winRunning();
};