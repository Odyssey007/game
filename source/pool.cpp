#include "../header/pool.h"

EnemyPool::EnemyPool(EnemyType type, size_t totalEnemies) : 
    totalEnemies(totalEnemies), currentNumEnemies(0)
{
    std::shared_ptr<Enemy> enemy;
    for (size_t i = 0; i < totalEnemies; ++i) {
        if (type == EnemyType::SLIME) {
            enemy = std::make_shared<Slime>();
        } //!more types
        pool.push_back(enemy);
    }
}

void EnemyPool::currentEnemies(size_t numEnemies, const sf::View& view, CollisionManager& manager) {
    currentNumEnemies = std::min(numEnemies, pool.size());
    for (size_t i = 0; i < currentNumEnemies && !pool.empty(); ++i) {
        std::shared_ptr<Enemy> enemy = pool.back();
        pool.pop_back();
        enemy->setInitialPosition(view);
        activeEnemies.push_back(enemy);
        manager.addEntity(enemy);
    }
}

void EnemyPool::update(const sf::Vector2f& target) {
    for (auto& enemy : activeEnemies) {
        if (enemy->isAlive()) {
            enemy->update(target);
        }
    }
}

bool EnemyPool::allDead() const {
    for (const auto& enemy : activeEnemies) {
        if (enemy->isAlive()) {
            return false;
        }
    }
    return true;
}

void EnemyPool::applyMovement() {
    for (auto& enemy : activeEnemies) {
        enemy->applyMovement();
    }
}

void EnemyPool::render(sf::RenderWindow& window) const {
    for (const auto& enemy : activeEnemies) {
        if (enemy->isAlive()) {
            enemy->render(window);
        }
    }
}

void EnemyPool::resetEnemies(CollisionManager& manager) {
    for (auto& enemy : activeEnemies) {
        manager.removeEntity(enemy);
        pool.push_back(enemy);
    }
    activeEnemies.clear();
}

//----------------

ObjectPool::ObjectPool(size_t totalObjects) :
    totalObjects(totalObjects), currentNumObjects(0) 
{
    for (size_t i = 0; i < totalObjects; ++i) {
        pool.push_back(std::make_shared<Object>());
    }
}

void ObjectPool::currentObjects(size_t numObjects, CollisionManager& manager) {
    activeObjects.clear();
    currentNumObjects = std::min(numObjects, pool.size());
    for (size_t i = 0; i < currentNumObjects && !pool.empty(); ++i) {
        std::shared_ptr<Object> object = pool.back();
        pool.pop_back();
        //object->setInitialPosition(resolution);
        activeObjects.push_back(object);
        manager.addObject(object);
    }
}

void ObjectPool::update() {
    //
}

void ObjectPool::resetObjects(CollisionManager& manager) {
    for (auto& object : activeObjects) {
        manager.removeObject(object);
        pool.push_back(object);
    }
    activeObjects.clear();
}

void ObjectPool::render(sf::RenderWindow& window) const {
    for (const auto& object : activeObjects) {
        object->render(window);
    }
}