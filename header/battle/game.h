#pragma once
//game engine
#include "../header/utility.h"
#include "../header/battle/collisionManager.h"
#include "../header/battle/player/player.h"
#include "../header/battle/enemies/slime.h"
#include "../header/battle/obstacles/object.h"
#include "../header/battle/player/abilities/ability.h"
#include "../header/battle/gridSystem.h"
#include "../header/battle/pool.h"

#include "../header/battle/menu.h"

#include "../header/battle/player/abilities/blast.h"

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

    bool once = true;
    std::vector<std::shared_ptr<Entity>> neighbors;
};