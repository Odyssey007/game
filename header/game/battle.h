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
#include "../header/game/states.h"
#include "../header/battle/player/abilities/blast.h"

#include "../header/battle/menu.h"


class BattleState : public States {
private:
    sf::Vector2u resolution;
    sf::View view;
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
    //void currentWindow(sf::RenderWindow& window);

    Menu menu;
    GameState gameState;

    BlastPool blastPool;
    sf::Clock fireCooldown;

    void checkGameEnd();
    void checkWave();
public:
    //constructor
    BattleState();
    //functions
    virtual void handleEvents(sf::RenderWindow& window, sf::Event& event) override;
    virtual void update(sf::RenderWindow& window, sf::Event& event) override;
    virtual void render(sf::RenderWindow& window) override;
    virtual void enter(sf::RenderWindow& window) override; 
    virtual StateMode getStateType() override; 
    virtual void exit() override; 

    sf::FloatRect screenPosition;
    sf::Vector2f mousePosition;
    sf::Vector2f playerPosition;
    sf::FloatRect playerBounds;




    bool once = true;
    std::vector<std::shared_ptr<Entity>> neighbors;
};