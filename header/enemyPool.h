#pragma once
#include "utility.h"
#include "slime.h"
#include "collisionManager.h"

class EnemyPool {
private: 
    size_t totalEnemies; 
    size_t currentNumEnemies; 
    std::vector<std::shared_ptr<Enemy>> pool;
    std::vector<std::shared_ptr<Enemy>> activeEnemies;
public:
    EnemyPool(EnemyType type, size_t totalEnemies); 
    void currentEnemies(size_t numEnemies, sf::Vector2u& resolution, CollisionManager& manager);
    void update(const sf::Vector2f& target);
    void applyMovement();
    void render(sf::RenderWindow& window);
    void resetEnemies(CollisionManager& manager);
    bool allDead() const;
};

class ObjectPool {
private: 
    size_t totalObjects; 
    size_t currentNumObjects; 
    std::vector<std::shared_ptr<Enemy>> pool;
    std::vector<std::shared_ptr<Enemy>> activeObjects;
public:
    ObjectPool(size_t totalObjects); 
    void currentObjects(size_t numObjects, sf::Vector2u& resolution, CollisionManager& manager);
    void update();
    void render(sf::RenderWindow& window);
    void resetObjects(CollisionManager& manager);
};