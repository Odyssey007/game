#include "../header/battle/player/abilities/dash.h"

Dash::Dash() {
    teleportRange = 100.0f;
    fireCooldown = 10.0f;
}

bool Dash::activate(const sf::Vector2f& mousePosition, sf::Vector2f& playerPosition) {
    sf::Vector2f canJump = mousePosition - playerPosition;
    if (magnitude(canJump) > teleportRange) {
        canJump = normalize(canJump) * teleportRange;
        playerPosition = playerPosition + canJump;
        return true;
    }
    return false;
}


/*
void Player::dash(const sf::Vector2f& mousePosition) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && dashClock.getElapsedTime().asSeconds() > dashCooldown) {
        isDashing = true;
        dashClock.restart();

        // Calculate move distance
        sf::Vector2f direction = mousePosition - sprite.getPosition();
        moveDistance = normalize(direction);
        totalDashDistance = 0; 
    }

    if (isDashing) {
        if (totalDashDistance < dashDistance) {
            sf::Vector2f move;
            move.x = moveDistance.x * DeltaTime::getInstance()->getDeltaTime() * 200 * 6;
            move.y = moveDistance.y * DeltaTime::getInstance()->getDeltaTime() * 200 * 6;

            sprite.move(move);
            hitBox.followEntity(sprite.getPosition());
            totalDashDistance += magnitude(move);
        } else {
            isDashing = false; 
        }
    }
}
*/