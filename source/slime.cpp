#include "../header/slime.h"

Slime::Slime() :
    needToCharge(false), chargeTimer(0.15f),
    needToRecover(false), recoveryTimer(0.15f),
    leapDistance(250.0f), totalLeapDistance(0.0f)
{
    movementSpeed = 280.0f;

    enemySprite.setTexture(enemyTextures["slime"]);
    //sets origin at the center of the sprite
    spriteBounds = enemySprite.getLocalBounds();
    enemySprite.setOrigin(spriteBounds.width / 2.0f, spriteBounds.height / 2.0f);
}

void Slime::action(const sf::Vector2f& target, const float attackRange) {
    // Check if recovery buffer is needed for attack  
    if (needToRecover) {
        if (recoveryTimer > 0) {
            recoveryTimer -= DeltaTime::getInstance()->getDeltaTime();
            recoveryTimer -= DeltaTime::getInstance()->getDeltaTime();
            return;
        }
        needToRecover = false;
    }
    //moves
    if (distance(target, enemySprite.getPosition()) >= attackRange && !needToCharge) {
        meleeMovement(target);
    } else { //attacks
        attacks(attackRange);
    }
}

void Slime::attacks(float attackRange) {
    if (attackRange >= 100) {
        leapAttack();
    } else if (attackRange >= 50) {
        normalAttack();
    }
}

void Slime::normalAttack() {

}

void Slime::leapAttack() {
    if (!needToCharge) {
        chargeTimer -= DeltaTime::getInstance()->getDeltaTime();
        if (chargeTimer <= 0) {
            needToCharge = true;
        }
    }
    if (totalLeapDistance < leapDistance && needToCharge) {
        float moveFrame = 5.5 * movementSpeed * DeltaTime::getInstance()->getDeltaTime();
        sf::Vector2f move = bestDirection * moveFrame;
        enemySprite.move(move);
        totalLeapDistance += magnitude(move);
    } else if (needToCharge) {
        totalLeapDistance = 0.0f;
        //start buffer
        needToCharge = false;
        chargeTimer = 0.15f;
        //end buffer
        needToRecover = true;
        recoveryTimer = 0.15f;
    }
}