#pragma once
//game engine
#include "../header/utility.h"
#include "../header/battle/collisionManager.h"
#include "../header/battle/player/player.h"
#include "../header/battle/enemies/slime.h"
#include "../header/battle/obstacles/pillar.h"
#include "../header/battle/player/abilities/ability.h"
#include "../header/battle/gridSystem.h"
#include "../header/battle/pool.h"

#include "../header/battle/menu.h"

#include "../header/battle/player/abilities/blast.h"

class Game {
private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    //
    sf::Texture cursorTexture;
    sf::Cursor cursor;
    //window reset up
    std::unique_ptr<sf::RenderWindow> window; 
    sf::Vector2u resolution;
    sf::View view;
    sf::Event event;
    //collision
    CollisionManager collisionManager;
    GridSystem grid; 
    //PLAYER
    std::unique_ptr<Player> player;
    //ENEMY
    //EnemyPool enemyPool; 
    std::unique_ptr<EnemyPool> enemyPool;
    std::unique_ptr<ObstaclePool> obstaclePool;
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


    BlastPool blastPool;
};