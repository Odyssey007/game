#include "../header/battle/enemies/enemyAbility.h"

EnemyAbility::EnemyAbility() {
    debuff = {0.0f, 0.0f};
    attackCooldown = 1.0f;
    overrideTimer = false;
}

sf::Vector2f EnemyAbility::attack() {
    return debuff;
}

float EnemyAbility::getAttackTimer() const {
    return attackTimer.getElapsedTime().asSeconds();
}

float EnemyAbility::getAttackCooldown() const {
    return attackCooldown;
}

bool EnemyAbility::newAttack() const {
    return overrideTimer;
}

void EnemyAbility::resetOverride() {
    overrideTimer = false;
}

void EnemyAbility::restartAttackTimer() {
    attackTimer.restart();
}

void EnemyAbility::handleCollision(Entity& entity) {
    return;
}