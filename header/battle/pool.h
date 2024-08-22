#pragma once
#include "../header/utility.h"
#include "../header/battle/enemies/slime.h"
#include "../header/battle/enemies/goblin.h"
#include "../header/battle/obstacles/pillar.h"
#include "../header/battle/gridSystem.h"

class EnemyPool {
private: 
    size_t totalEnemies; 
    size_t currentNumEnemies; 
    std::vector<std::unique_ptr<Enemy>> pool;
    std::vector<std::unique_ptr<Enemy>> activeEnemies;
    EnemyType getEnemyType();
public:
    EnemyPool(size_t totalEnemies); 
    void currentEnemies(size_t numEnemies, const sf::FloatRect& screenBounds, GridSystem& grid);
    void update(const sf::Vector2f& target);
    void applyMovement();
    void render(sf::RenderWindow& window) const;
    void resetEnemies();
};

class ObstaclePool {
private: 
    size_t totalObstacle; 
    std::vector<std::unique_ptr<Pillar>> activeObstacle;
public:
    ObstaclePool(size_t totalObstacle); 
    void currentObjects(const sf::FloatRect& screenBounds, GridSystem& grid);
    void update(const sf::FloatRect& screenBounds);
    void render(sf::RenderWindow& window) const;
    void resetObjects();
};