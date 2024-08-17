#pragma once
#include "../header/utility.h"
#include "../header/battle/enemies/slime.h"
#include "../header/battle/enemies/goblin.h"
#include "../header/battle/obstacles/object.h"
#include "../header/battle/gridSystem.h"

class EnemyPool {
private: 
    size_t totalEnemies; 
    size_t currentNumEnemies; 
    std::vector<std::shared_ptr<Enemy>> pool;
    EnemyType getEnemyType();
public:
    std::vector<std::shared_ptr<Enemy>> activeEnemies;
    EnemyPool(size_t totalEnemies); 
    void currentEnemies(size_t numEnemies, const sf::FloatRect& screenBounds, GridSystem& grid);
    void update(const sf::Vector2f& target);
    void applyMovement();
    void render(sf::RenderWindow& window) const;
    void resetEnemies();
    bool allDead() const;
};

class ObjectPool {
private: 
    size_t totalObjects; 
    size_t currentNumObjects; 
    std::vector<std::shared_ptr<Object>> pool;
public:
    std::vector<std::shared_ptr<Object>> activeObjects;
    ObjectPool(size_t totalObjects); 
    void currentObjects(size_t numObjects, const sf::FloatRect& screenBounds, GridSystem& grid);
    void update();
    void render(sf::RenderWindow& window) const;
    void resetObjects();
};