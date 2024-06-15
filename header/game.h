#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
//?pre-compiled header
//game engine
#include <../header/player.h>

class Game {
private:
    //window set up
    sf::RenderWindow* window; //the current window the game is in
    sf::VideoMode resolution; //controls the resolution of screen
    sf::Event event;

    void curWindow();
public:
    Game(); //constructor
    ~Game(); //destructor

    Player player; 

    //checks
    bool winRunning() const;
    //functions
    void update();
    void render();
};