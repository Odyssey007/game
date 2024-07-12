#pragma once
//game engine
#include "utility.h"
#include "collisionManager.h"
#include "player.h"
#include "slime.h"
#include "obstacles.h"
#include "ability.h"
#include "quadtree.h"
#include "pool.h"

class Game {
private:
    //window reset up
    std::unique_ptr<sf::RenderWindow> window; 
    sf::Vector2u resolution;
    sf::View view;
    sf::Event event;
    //collision
    CollisionManager collisionManager;
    QuadTree quadTree;
    //PLAYER
    std::shared_ptr<Player> player;
    //ENEMY
    EnemyPool enemyPool; 
    size_t currentWave;
    sf::Clock waveClock;
    sf::Time waveTimer;
    //OBJECTS
    ObjectPool objectPool;
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