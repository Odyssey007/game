#pragma once
#include "../header/utility.h"
#include "../header/battle/enemies/slime.h"
#include "../header/battle/enemies/goblin.h"
#include "../header/battle/obstacles/pillar.h"
#include "../header/battle/gridSystem.h"
#include "../header/battle/enemies/exp.h"

class EnemyPool {
private: 
    size_t totalEnemies; 
    size_t currentNumEnemies;
    std::vector<std::unique_ptr<Enemy>> pool;
    std::vector<std::unique_ptr<Enemy>> activeEnemies;
    //exp
    std::vector<std::unique_ptr<Exp>> expPool;
    std::vector<std::unique_ptr<Exp>> expDrops;
    EnemyType getEnemyType();
public:
    EnemyPool(const size_t totalEnemies); 
    void spawnEnemies(const size_t numEnemies, const size_t level, 
                      const sf::FloatRect& screenBounds, GridSystem& grid);
    void update(const sf::Vector2f& target);
    bool isAllDead();
    void applyMovement();
    void renderEnemies(sf::RenderWindow& window) const;
    void resetEnemies(GridSystem& grid);
    //exp
    void expDrop(GridSystem& grid, const sf::FloatRect& enemy);
    void renderExp(sf::RenderWindow& window) const;
};

class ObstaclePool {
private: 
    size_t totalObstacle; 
    std::vector<std::unique_ptr<Pillar>> activeObstacle;
public:
    ObstaclePool(const size_t totalObjects, const sf::FloatRect& screenBounds, GridSystem& grid); 
    void update(const sf::FloatRect& screenBounds);
    void render(sf::RenderWindow& window) const;
    void resetObjects();
};