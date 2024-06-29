#include "../header/slime.h"

Slime::Slime() {
    movementSpeed = 150.0f;
    needRecovery = false; 
    recoveryTimer = 0.25f;
    enemySprite.setTexture(enemyTextures["slime"]);
    //sets origin at the center of the sprite
    spriteBounds = enemySprite.getLocalBounds();
    enemySprite.setOrigin(spriteBounds.width / 2.0f, spriteBounds.height / 2.0f);
}

void Slime::action(const sf::Vector2f& target, const float attackRange) {
    // Check if recovery buffer is needed for attack  
    if (needRecovery) {
        if (recoveryTimer > 0) {
            recoveryTimer -= DeltaTime::getInstance()->getDeltaTime();
            return;
        }
        needRecovery = false;
    }
    //moves
    if (distance(target, enemySprite.getPosition()) >= attackRange && !isAttacking) {
        maleeMovement(target);
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
    if (!isAttacking) {
        leapStartBuffer -= DeltaTime::getInstance()->getDeltaTime();
        if (leapStartBuffer <= 0) {
            isAttacking = true;
        }
    }
    if (totalLeapDistance < leapDistance && isAttacking) {
        float moveFrame = 5.5 * movementSpeed * DeltaTime::getInstance()->getDeltaTime();
        sf::Vector2f move = bestDirection * moveFrame;
        enemySprite.move(move);
        totalLeapDistance += magnitude(move);
    } else if (isAttacking) {
        totalLeapDistance = 0.0f;
        //start buffer
        isAttacking = false;
        leapStartBuffer = 0.15f;
        //end buffer
        needRecovery = true;
        recoveryTimer = 0.15f;
    }
}