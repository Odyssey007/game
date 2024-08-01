#pragma once
#include "../header/utility.h"
#include "../header/enemies/slime.h"
#include "../header/collisionManager.h"

class EnemyPool {
private: 
    size_t totalEnemies; 
    size_t currentNumEnemies; 
    std::vector<std::shared_ptr<Enemy>> pool;
public:
    std::vector<std::shared_ptr<Enemy>> activeEnemies;
    EnemyPool(EnemyType type, size_t totalEnemies); 
    void currentEnemies(size_t numEnemies, const sf::View& view, CollisionManager& manager);
    void update(const sf::Vector2f& target);
    void applyMovement();
    void render(sf::RenderWindow& window) const;
    void resetEnemies(CollisionManager& manager);
    bool allDead() const;
};

class ObjectPool {
private: 
    size_t totalObjects; 
    size_t currentNumObjects; 
    std::vector<std::shared_ptr<Object>> pool;
    std::vector<std::shared_ptr<Object>> activeObjects;
public:
    ObjectPool(size_t totalObjects); 
    void currentObjects(size_t numObjects, const sf::View& view, CollisionManager& manager);
    void update();
    void render(sf::RenderWindow& window) const;
    void resetObjects(CollisionManager& manager);
};