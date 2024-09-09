#pragma once
#include "../header/utility.h"
#include "../header/battle/player/abilities/ability.h"

class Dash {
private:
    sf::Clock cooldownTimer;
    float cooldown;
    bool first;
    //
    bool isDashing;
    bool dashActivate;
    //buffer
    float chargeTimer;
    //distance
    float curDashDistance;
    float totalDashDistance;
    //
    sf::Vector2f dashDirection;
    float dashSpeed;
    void reset();
public:
    Dash();
    bool activate(const sf::Vector2f& dashDir, const sf::Vector2f& playerPos);
    bool getIsDashing() const;
    void update(bool& colliding, sf::Vector2f& moveDistance);
};