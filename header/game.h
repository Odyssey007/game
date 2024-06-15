#pragma once

#include <SFML/Graphics.hpp>
//?pre-compiled header
//game engine

class Game {
private:
    sf::RenderWindow* window; //the current window the game is in
    sf::VideoMode resolution; //controls the resolution of screen
    sf::Event event;

    void curWindow();

public:
    Game(); //constructor
    ~Game(); //destructor

    const bool winRunning() const; 

    void update();
    void render();
};