#pragma once
#include "utility.h"
#include "enemy.h"

class Slime : public Enemy{
private:
    //buffer for leap
    float leapStartBuffer = 0.25f;
    bool recovering = false;
    float leapEndBuffer = 0.25f;
    //leap distance
    float leapDistance = 250.0f;
    float totalLeapDistance = 0.0f;

    virtual void attacks(float attackRange) override;
public:
    Slime();

    void action(const sf::Vector2f& target, const float attackRange);
    void leapAttack();
    void normalAttack();

    //for recovery
    bool needRecovery;
    float recoveryTimer;

    bool isAttacking = false;
    
};