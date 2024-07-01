#include "../header/slime.h"

Slime::Slime() :
    leaping(false), chargeTimer(0.35f),
    needToRecover(false), recoveryTimer(0.35f),
    leapDistance(250.0f), totalLeapDistance(0.0f)
{
    firstAttack = true;
    //movement and sprite
    movementSpeed = 200.0f;
    enemySprite.setTexture(enemyTextures["slime"]);

    //set position
    enemySprite.setPosition(1000, 1000);

    sf::Image image = enemyTextures["slime"].copyToImage();
    //sets the origin of slime and hitbox
    spriteBounds = boxBoundsCalc(image);
    hitbox.updateSize(spriteBounds);
    sf::Vector2f origin;
    origin.x = spriteBounds.left + spriteBounds.width/2.0f;
    origin.y = spriteBounds.top + spriteBounds.height/2.0f;
    enemySprite.setOrigin(origin);
}

void Slime::action(const sf::Vector2f& target, const float canLeap) {
    // Check if recovery buffer is needed for attack  
    if (needToRecover) {
        if (recoveryTimer > 0) {
            recoveryTimer -= DeltaTime::getInstance()->getDeltaTime();
            return;
        }
        needToRecover = false;
    }
    //moves
    hitbox.followEntity(enemySprite.getPosition());
    if (distance(target, enemySprite.getPosition()) >= canLeap && !leaping) {
        meleeMovement(target);
    } else { //attacks
        attacks();
    }
}
/*
normal attacks takes time to charge 

initially the charge time is 0 however if the slime attacks and not move then charge time is X
*/

void Slime::attacks() {
    if (firstAttack) {
        dmg = 10.0f;
        leapAttack();
    }
    dmg = 5.0f;
    normalAttack();
}

void Slime::normalAttack() {
    
}

void Slime::leapAttack() {
    if (!leaping) {
        chargeTimer -= DeltaTime::getInstance()->getDeltaTime();
        if (chargeTimer <= 0) {
            leaping = true;
        }
    }
    if (totalLeapDistance < leapDistance && leaping) {
        float moveFrame = 5.5 * movementSpeed * DeltaTime::getInstance()->getDeltaTime();
        sf::Vector2f move = bestDirection * moveFrame;
        enemySprite.move(move);
        totalLeapDistance += magnitude(move);
    } else if (leaping) {
        totalLeapDistance = 0.0f;
        //start buffer
        leaping = false;
        chargeTimer = 0.35f;
        //end buffer
        needToRecover = true;
        recoveryTimer = 0.35f;
    }
}