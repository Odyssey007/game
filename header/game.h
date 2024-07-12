#pragma once
//game engine
#include "utility.h"
#include "collisionManager.h"
#include "player.h"
#include "slime.h"
#include "obstacles.h"
#include "ability.h"
#include "quadtree.h"
#include "enemyPool.h"

class Game {
private:
    //window reset up
    std::unique_ptr<sf::RenderWindow> window; 
    sf::Vector2u resolution;
    sf::View view;
    sf::Event event;
    //collision
    CollisionManager collisionManager;
    //PLAYER
    std::shared_ptr<Player> player;
    //ENEMY
    EnemyPool enemyPool; 
    size_t currentWave;
    sf::Clock waveClock;
    sf::Time waveTimer;
    //OBJECTS
    size_t objectNum;
    std::shared_ptr<std::vector<std::shared_ptr<Object>>> objects;
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

    void checkWave();
};