#include "../header/enemyPool.h"

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

void EnemyPool::currentEnemies(size_t numEnemies, sf::Vector2u& resolution, CollisionManager& manager) {
    activeEnemies.clear();
    currentNumEnemies = std::min(numEnemies, pool.size());
    for (size_t i = 0; i < currentNumEnemies && !pool.empty(); ++i) {
        std::shared_ptr<Enemy> enemy = pool.back();
        pool.pop_back();
        enemy->setInitialPosition(resolution);
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
    for (auto& enemy : activeEnemies) {
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

void EnemyPool::render(sf::RenderWindow& window) {
    for (auto& enemy : activeEnemies) {
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