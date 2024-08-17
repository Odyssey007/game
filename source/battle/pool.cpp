#include "../header/battle/pool.h"

EnemyPool::EnemyPool(size_t totalEnemies) : 
    totalEnemies(totalEnemies), currentNumEnemies(0)
{
    std::shared_ptr<Enemy> enemy;
    for (size_t i = 0; i < totalEnemies; ++i) {
        EnemyType type = getEnemyType();
        switch (type) {
            case EnemyType::SLIME:
                enemy = std::make_shared<Slime>();
                break;
            case EnemyType::GOBLIN:
                enemy = std::make_shared<Goblin>();
                break;
        }
        pool.emplace_back(enemy);
    }
}

EnemyType EnemyPool::getEnemyType() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    return static_cast<EnemyType>(dis(gen));
}

void EnemyPool::currentEnemies(size_t numEnemies, const sf::FloatRect& screenBounds, GridSystem& grid) {
    currentNumEnemies = std::min(numEnemies, pool.size());
    for (size_t i = 0; i < currentNumEnemies && !pool.empty(); ++i) {
        std::shared_ptr<Enemy> enemy = pool.back();
        pool.pop_back();
        enemy->setInitialPosition(screenBounds);
        activeEnemies.push_back(enemy);
        grid.addEntity(enemy);
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

void EnemyPool::resetEnemies() {
    for (auto& enemy : activeEnemies) {
        pool.push_back(enemy);
    }
    activeEnemies.clear();
}

//----------------

ObjectPool::ObjectPool(size_t totalObjects) :
    totalObjects(totalObjects), currentNumObjects(0) 
{
    for (size_t i = 0; i < totalObjects; ++i) {
        pool.emplace_back(std::make_shared<Object>());
    }
}

void ObjectPool::currentObjects(size_t numObjects, const sf::FloatRect& screenBounds, GridSystem& grid) {
    activeObjects.clear();
    currentNumObjects = std::min(numObjects, pool.size());
    for (size_t i = 0; i < currentNumObjects && !pool.empty(); ++i) {
        std::shared_ptr<Object> object = pool.back();
        pool.pop_back();
        object->setInitialPosition(screenBounds);
        activeObjects.push_back(object);
        grid.addEntity(object);
    }
}

void ObjectPool::update() {
    //
}

void ObjectPool::resetObjects() {
    for (auto& object : activeObjects) {
        pool.push_back(object);
    }
    activeObjects.clear();
}

void ObjectPool::render(sf::RenderWindow& window) const {
    for (const auto& object : activeObjects) {
        object->render(window);
    }
}