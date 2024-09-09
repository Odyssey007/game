#include "../header/battle/player/abilities/dash.h"

Dash::Dash() {
    dashActivate = false; isDashing = false;
    //buffer
    chargeTimer = 0.15f; 
    //distance
    curDashDistance = 0.0f; 
    totalDashDistance = 150.0f;
    //
    cooldown = 0.5f; first = true;
}

//? disgusting: when you dash into horizontal pillar in the middle it lets you walk thru???

bool Dash::activate(const sf::Vector2f& dashDir, const sf::Vector2f& playerPos) {
    if (cooldownTimer.getElapsedTime().asSeconds() >= cooldown || first) {
        dashActivate = true; first = false;
        dashDirection = dashDir;
        return true;
    }
    return false;
}

bool Dash::getIsDashing() const {
    return isDashing;
}

void Dash::update(bool& colliding, sf::Vector2f& moveDistance) {
    if (!dashActivate) {
        return;
    }
    //dash buffer
    if (!isDashing) {
        chargeTimer -= DeltaTime::getInstance()->getDeltaTime();
        if (chargeTimer <= 0) {
            isDashing = true;
        } else {
            return;
        }
    }
    //stops once it hits obstacle
    if (isDashing && colliding) { 
        dashDirection = sf::Vector2f(0,0);
        colliding = false;
        reset(); //force end of dash
        return;
    }
    //dashes
    if (isDashing) {        
        if (curDashDistance < totalDashDistance) {
            float moveFrame = 5.5f * 350.0f * DeltaTime::getInstance()->getDeltaTime();
            moveDistance = dashDirection * moveFrame;
            curDashDistance += magnitude(moveDistance);
        } else { 
            reset(); //end of dash
        }
    }
}

void Dash::reset() {
    dashActivate = false; 
    isDashing = false;
    curDashDistance = 0.0f;
    chargeTimer = 0.15f;
    //
    cooldownTimer.restart();
}