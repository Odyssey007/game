#pragma once
#include "utility.h"
#include "enemy.h"

#include "collision.h"

class Slime : public Enemy{
private:
    //buffer for leap
    bool needToCharge;
    float chargeTimer;
    //recovery
    bool needToRecover;
    float recoveryTimer;
    //leap distance
    float leapDistance;
    float totalLeapDistance;

    virtual void attacks(float attackRange) override;
public:
    Slime();

    void action(const sf::Vector2f& target, const float attackRange);
    void leapAttack();
    void normalAttack();

    RecCollision hitbox;
};