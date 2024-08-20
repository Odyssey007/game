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
    bool allDead() const;
};

class ObstaclePool {
private: 
    std::vector<std::unique_ptr<Pillar>> activeObstacles;
public:
    ObstaclePool() = delete;
    ObstaclePool(GridSystem& grid, const sf::FloatRect& screenBounds); 
    void update(const sf::FloatRect& screenBounds);
    void render(sf::RenderWindow& window) const;
    void removeObstacles(GridSystem& grid);
};