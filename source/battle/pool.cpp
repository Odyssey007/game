#include "../header/battle/pool.h"

//todo spawns in exp out of nowhere (random kill spawns in more exp then supposed to)
//todo spawns the ghost horde 🙏🙏

EnemyPool::EnemyPool(const size_t totalEnemies) : 
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
    //?change amount....maybe
    for (size_t i = 0; i < 150; ++i) {
        expPool.emplace_back(std::make_unique<Exp>());
    }
}

EnemyType EnemyPool::getEnemyType() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    return static_cast<EnemyType>(dis(gen));
}

void EnemyPool::spawnEnemies(const size_t numEnemies, const size_t level, 
                             const sf::FloatRect& screenBounds, GridSystem& grid) {
    currentNumEnemies = std::min(numEnemies, pool.size());
    for (size_t i = 0; i < currentNumEnemies && !pool.empty(); ++i) {
        auto enemy = std::move(pool.back());
        pool.pop_back();
        enemy->spawn(level, screenBounds);
        grid.addEntity(*enemy);
        activeEnemies.push_back(std::move(enemy));
    }
}

void EnemyPool::update(const sf::Vector2f& target) {
    for (auto& enemy : activeEnemies) {
        enemy->checkAlive();
        if (enemy->isAlive()) {
            enemy->update(target);
        }
    }
    //exp
    for (auto& exp : expDrops) {
        exp->update(target);
        exp->applyMovement();
    }
}

bool EnemyPool::isAllDead() {
    return activeEnemies.empty();
}

void EnemyPool::applyMovement() {
    for (auto& enemy : activeEnemies) {
        enemy->applyMovement();
    }
}

void EnemyPool::renderEnemies(sf::RenderWindow& window) const {
    for (const auto& enemy : activeEnemies) {
        enemy->render(window);
    }
}

void EnemyPool::renderExp(sf::RenderWindow& window) const {
    for (const auto& exp : expDrops) {
        exp->render(window);
    }
}

void EnemyPool::resetEnemies(GridSystem& grid) {
    //enemies
    for (auto it = activeEnemies.begin(); it != activeEnemies.end(); ) {
        if (!(*it)->isAlive()) {
            expDrop(grid, (*it)->getBounds());
            pool.push_back(std::move(*it));
            it = activeEnemies.erase(it);
        } else {
            ++it;
        }
    }
    //exp
    for (auto it = expDrops.begin(); it != expDrops.end(); ) {
        if (!(*it)->isAlive()) {
            expPool.push_back(std::move(*it));
            it = expDrops.erase(it);
        } else {
            ++it;
        }
    }
}

void EnemyPool::expDrop(GridSystem& grid, const sf::FloatRect& enemy) {
    if (!expPool.empty()) {
        auto exp = std::move(expPool.back());
        expPool.pop_back();
        exp->spawn(enemy);
        grid.addEntity(*exp);
        expDrops.push_back(std::move(exp));
    }
}

//---------

ObstaclePool::ObstaclePool(const size_t totalObjects, const sf::FloatRect& screenBounds, GridSystem& grid) :
    totalObstacle(totalObjects) 
{
    for (size_t i = 0; i < totalObjects; ++i) {
        activeObstacle.emplace_back(std::make_unique<Pillar>());
        activeObstacle[i]->setInitialPosition(screenBounds);
        grid.addEntity(*activeObstacle[i]);
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
        if (object->isAlive()) {
            object->render(window);
        }
    }
}