#pragma once
//game engine
#include "../header/utility.h"
#include "../header/collisionManager.h"
#include "../header/player/player.h"
#include "../header/enemies/slime.h"
#include "../header/obstacles/object.h"
#include "../header/player/abilities/ability.h"
#include "../header/quadtree.h"
#include "../header/pool.h"

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
    Grid grid; 
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