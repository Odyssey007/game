#include "../header/battle/pool.h"

EnemyPool::EnemyPool(size_t totalEnemies) : 
    totalEnemies(totalEnemies), currentNumEnemies(0)
{
    for (size_t i = 0; i < totalEnemies; ++i) {
        EnemyType type = getEnemyType();
        switch (type) {
            case EnemyType::SLIME:
                pool.emplace_back(std::make_unique<Slime>());
                break;
            case EnemyType::GOBLIN:
                pool.emplace_back(std::make_unique<Goblin>());
                break;
        }
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
        pool.push_back(std::move(enemy));
    }
    activeEnemies.clear();
}

//----------------

ObstaclePool::ObstaclePool(GridSystem& grid, const sf::FloatRect& screenBounds) {
    for (size_t i = 0; i < 4; ++i) {
        std::unique_ptr<Pillar> pillar = std::make_unique<Pillar>();
        pillar->setInitialPosition(screenBounds);
        grid.addEntity(*pillar);
        activeObstacles.emplace_back(std::move(pillar));
    }
}

void ObstaclePool::update(const sf::FloatRect& screenBounds) {
    for (auto& obstacle : activeObstacles) {
        obstacle->respawn(screenBounds);
    }
}

void ObstaclePool::removeObstacles(GridSystem& grid) {
    //
}

void ObstaclePool::render(sf::RenderWindow& window) const {
    for (const auto& obstacle : activeObstacles) {
        if (obstacle->isAlive()) {
            obstacle->render(window);
        }
    }
}