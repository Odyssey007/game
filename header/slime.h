#pragma once
#include "utility.h"
#include "enemy.h"

#include "collision.h"

class Slime : public Enemy{
private:
    bool firstAttack;
    //buffer for leap
    bool leaping;
    float chargeTimer;
    //recovery
    bool needToRecover;
    float recoveryTimer;
    //leap distance
    float leapDistance;
    float totalLeapDistance;

    virtual void attacks() override;
public:
    Slime();

    void action(const sf::Vector2f& target, const float attackRange);
    void leapAttack();
    void normalAttack();

    RecCollision hitBox;
    CircleCollision hitBoxC;


    float dmg = 5.0f;
};