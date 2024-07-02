#pragma once
//game engine
#include "player.h"
#include "slime.h"
#include "ability.h"

class Game {
private:
    //window set up
    std::unique_ptr <sf::RenderWindow> window; //the current window the game is in
    sf::VideoMode resolution; //controls the resolution of screen
    sf::Event event;
    Player player;
    Sword sword; 
    Slime s1;
    Ability ability; 

    void currentWindow();
public:
    Game(); //constructor


    //checks
    bool winRunning() const;
    //functions
    void handleEvents();
    void update();
    void render();

    void checkCollision();

    //CollisionManager collisions;
};