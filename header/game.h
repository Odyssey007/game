#pragma once
//game engine
#include "utility.h"
#include "collisionManager.h"
#include "player.h"
#include "slime.h"
#include "obstacles.h"
#include "ability.h"

class Game {
private:
    //window reset up
    std::unique_ptr <sf::RenderWindow> window; 
    sf::Vector2u resolution;
    sf::Event event;
    //collision big papa
    CollisionManager collisionManager;
    //entities
    std::shared_ptr<Player> player;
    size_t slimeNum;
    std::shared_ptr<std::vector<std::shared_ptr<Slime>>> slimes;
    size_t staticObstacleNum;
    std::shared_ptr<std::vector<std::shared_ptr<StaticObstacle>>> staticObstacles;
    //functions
    void currentWindow();
    void handleEvents();
    void checkGameEnd();
public:
    //constructor
    Game();
    //functions
    void update();
    void render();
    bool winRunning() const;
};