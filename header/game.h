#pragma once
//game engine
#include "../header/utility.h"
#include "../header/collisionManager.h"
#include "../header/player/player.h"
#include "../header/enemies/slime.h"
#include "../header/obstacles/object.h"
#include "../header/player/abilities/ability.h"
#include "../header/gridSystem.h"
#include "../header/pool.h"

#include "../header/menu.h"

#include "../header/player/abilities/blast.h"

class Game {
private:
    //window reset up
    std::unique_ptr<sf::RenderWindow> window; 
    sf::Vector2u resolution;
    sf::View view;
    sf::Event event;
    //collision
    CollisionManager collisionManager;
    GridSystem grid; 
    //PLAYER
    std::shared_ptr<Player> player;
    //ENEMY
    //EnemyPool enemyPool; 
    std::shared_ptr<EnemyPool> enemyPool;
    std::shared_ptr<ObjectPool> objectPool;
    size_t currentWave;
    sf::Clock waveClock;
    sf::Time waveTimer;
    //OBJECTS
    //ObjectPool objectPool;
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

    sf::FloatRect screenBounds;
    sf::Vector2f mousePosition;
    sf::Vector2f playerPosition;
    sf::FloatRect playerBounds;


    Menu menu;
    GameState gameState;

    sf::Clock fireCooldown;
    BlastPool blastPool;
    Blast blast;


    bool once = true;
    std::vector<std::shared_ptr<Entity>> neighbors;
};