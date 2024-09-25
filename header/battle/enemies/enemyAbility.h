#pragma once
#include "../header/battle/enemies/enemy.h"

class EnemyAbility : public Entity {
protected:
    sf::Vector2f debuff;
    //
    sf::Clock attackTimer;
    float attackCooldown;
    bool overrideTimer;
public:
    EnemyAbility();
    bool newAttack() const;
    float getAttackTimer() const;
    float getAttackCooldown() const;
    void resetOverride();
    void restartAttackTimer();
    //
    virtual sf::Vector2f attack();
    virtual void activate(const sf::Vector2f& bossPos) = 0;
    //
    virtual void handleCollision(Entity& entity) override;
};