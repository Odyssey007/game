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
#include "../header/battle/enemies/exp.h"

class Game {
private:
    //set up
    std::unique_ptr<sf::RenderWindow> window; 
    sf::Vector2u resolution;
    sf::View view;
    sf::Event event;
    GridSystem grid; 
    //entities
    std::unique_ptr<Player> player;
    std::unique_ptr<EnemyPool> enemyPool;
    std::unique_ptr<ObstaclePool> obstaclePool;
    //wave
    size_t currentWave;
    sf::Clock waveClock;
    sf::Time waveTimer;
    //info storage
    sf::FloatRect screenBounds;
    sf::Vector2f mousePosition;
    sf::Vector2f playerPosition;
    sf::FloatRect playerBounds;
    //functions
    void currentWindow();
    void handleEvents();
public:
    //constructor
    Game();
    //functions
    void update();
    void render();
    bool winRunning() const;


    //!not finalized

    //wave
    void checkWave();
    void checkGameEnd();
    //menu
    Menu menu;
    GameState gameState;
    //ability
    bool abilityActive = false;
    BlastPool blastPool; //blast
};