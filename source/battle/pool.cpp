#include "../header/battle/pool.h"

EnemyPool::EnemyPool(size_t totalEnemies) : 
    totalEnemies(totalEnemies), currentNumEnemies(0)
{
    std::unique_ptr<Enemy> enemy;
    for (size_t i = 0; i < totalEnemies; ++i) {
        EnemyType type = getEnemyType();
        switch (type) {
            case EnemyType::SLIME:
                enemy = std::make_unique<Slime>();
                break;
            case EnemyType::GOBLIN:
                enemy = std::make_unique<Goblin>();
                break;
        }
        pool.emplace_back(std::move(enemy));
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
        auto enemy = std::move(pool.back());
        pool.pop_back();
        enemy->setInitialPosition(screenBounds);
        grid.addEntity(*enemy);
        activeEnemies.push_back(std::move(enemy));
    }
}

void EnemyPool::update(const sf::Vector2f& target) {
    for (auto& enemy : activeEnemies) {
        if (enemy->alive) {
            enemy->update(target);
        }
    }
}

void EnemyPool::applyMovement() {
    for (auto& enemy : activeEnemies) {
        enemy->applyMovement();
    }
}

void EnemyPool::render(sf::RenderWindow& window) const {
    for (const auto& enemy : activeEnemies) {
        enemy->render(window);
    }
}

void EnemyPool::resetEnemies() {
    for (auto it = activeEnemies.begin(); it != activeEnemies.end(); ) {
        if (!(*it)->alive) {
            pool.push_back(std::move(*it));
            it = activeEnemies.erase(it);
        } else {
            ++it;
        }
    }
}

//---------

ObstaclePool::ObstaclePool(size_t totalObjects) :
    totalObstacle(totalObjects) 
{
    for (size_t i = 0; i < totalObjects; ++i) {
        activeObstacle.emplace_back(std::make_unique<Pillar>()); 
    }
}

void ObstaclePool::currentObjects(const sf::FloatRect& screenBounds, GridSystem& grid) {
    for (auto& object : activeObstacle) {
        object->startPos(screenBounds);
        grid.addEntity(*object);
    }
}

void ObstaclePool::update(const sf::FloatRect& screenBounds) {
    for (auto& obstacle : activeObstacle) {
        obstacle->respawn(screenBounds);
    }
}

void ObstaclePool::resetObjects() {
    // 
}

void ObstaclePool::render(sf::RenderWindow& window) const {
    for (const auto& object : activeObstacle) {
        if (object->alive) {
            object->render(window);
        }
    }
}