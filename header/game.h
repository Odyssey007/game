#pragma once
#include <cmath>
#include <string>
#include <memory>
#include <iostream> 
#include <SFML/Graphics.hpp>
//game engine
#include <../header/player.h>
#include <../header/enemy.h>

class Game {
private:
    //window set up
    std::unique_ptr <sf::RenderWindow> window; //the current window the game is in
    sf::VideoMode resolution; //controls the resolution of screen
    sf::Event event;
    Player player;
    Enemy slime;

    void currentWindow();
public:
    Game(); //constructor


    //checks
    bool winRunning() const;
    //functions
    void handleEvents();
    void update(float deltaTime);
    void render();

};