#pragma once 
#include "../header/utility.h"

enum StateMode {KINGDOM, BATTLE}; 

class States {
public: 
    StateMode mode;
    //Constructor and destructor 
    States() = default; 
    ~States() = default; 

    //GameLoop functions 
    virtual void render(sf::RenderWindow& window) = 0; 
    virtual void update(sf::RenderWindow& window, sf::Event& event) = 0; 
    virtual void handleEvents(sf::RenderWindow& window, sf::Event& event) = 0; 

    //Changing states 
    virtual void enter(sf::RenderWindow& window) = 0; 
    virtual void exit() = 0; 
    virtual StateMode getStateType() = 0; 
};