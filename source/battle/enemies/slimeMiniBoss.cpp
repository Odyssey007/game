#include "../header/battle/enemies/slimeMiniBoss.h"

const float BASE_MOVEMENT_SPEED = 185.0f;
const float BASE_SLOW = 0.0f; //done in %
const float BASE_DMG = 12.0f;
const float BASE_HP = 250.0f;
//ABILITY 1
const float ABILITY1_SLOW = 0.85f;
const float ABILITY1_DMG = 15.0f;

SlimeMiniBoss::SlimeMiniBoss() : 
    scale(1.3f), //mini
    //leap buffers
    leaping(false), leapingSpeed(5.5f), chargeTimer(0.35f), needToRecover(false), recoveryTimer(0.35f),
    //leap distance
    leapDistance(275.0f), totalLeapDistance(0.0f)
{
    collisionType = CIRCLE; //update entity-parent
    //update enemy-parent
    movementSpeed = BASE_MOVEMENT_SPEED;
    debuff = {BASE_DMG, BASE_SLOW}; health = BASE_HP;
    bounds = sf::FloatRect(39, 65, 75, 62);
    //mini-boss
    sprite.setScale(scale, scale);
    sprite.setColor(sf::Color(236, 59, 59));
    //
    sprite.setTexture(*textures["slime"]);
    hitBox.updateSize(bounds);
    sprite.setOrigin(sf::Vector2f((bounds.left + bounds.width/2.0f), (bounds.top + bounds.height/2.0f)));
}

void SlimeMiniBoss::update(const sf::Vector2f& target) {
    if (isSlowed) {
        slowDuration -= DeltaTime::getInstance()->getDeltaTime();
    }
    if (isSlowed && slowDuration <= 0) {
        isSlowed = false;
        slowDuration = 1.0f;
        movementSpeed = BASE_MOVEMENT_SPEED;
    }
    //changing direction
    sf::Vector2f toTarget = target - sprite.getPosition();
    toTarget = normalize(toTarget);
    if (toTarget.x >= 0) {
        facingRight = true;
    } else if (toTarget.x < 0) {
        facingRight = false;
    }

    if (facingRight) {
        sprite.setScale(scale, scale); 
    } 
    else {
        sprite.setScale(-scale, scale);
    }
    // Check if recovery buffer is needed for attack  
    if (needToRecover) {
        if (recoveryTimer > 0) {
            recoveryTimer -= DeltaTime::getInstance()->getDeltaTime();
            return;
        }
        needToRecover = false;
    }

    //moves
    if (distance(target, sprite.getPosition()) >= 125.0f && !leaping) {
        meleeMovement(target);
    } else {
        leapAttack();
    }
    hitBox.followEntity(sprite.getPosition());
}

void SlimeMiniBoss::leapAttack() {
    if (!leaping) {
        chargeTimer -= DeltaTime::getInstance()->getDeltaTime();
        if (chargeTimer <= 0) {
            leaping = true;
            chargeTimer = 0.35f;
            //
            debuff.x = ABILITY1_DMG;
            debuff.y = ABILITY1_SLOW;
        }
        return;
    }
    if (totalLeapDistance < leapDistance && leaping) {
        float moveFrame = leapingSpeed * movementSpeed * DeltaTime::getInstance()->getDeltaTime();
        sf::Vector2f move = bestDirection * moveFrame;
        sprite.move(move);
        hitBox.followEntity(sprite.getPosition());
        totalLeapDistance += magnitude(move);
    } else if (leaping) {
        //start recovery
        needToRecover = true;
        recoveryTimer = 0.35f;
        //reset
        totalLeapDistance = 0.0f;
        leaping = false;
        debuff.x = BASE_DMG;
        debuff.y = BASE_SLOW;
    }
}

void SlimeMiniBoss::checkLvlUp(const size_t level) {
    if (level == 0) return;
    health += BASE_HP*level*0.1f;
    debuff.x += BASE_DMG*level*0.05f;
    movementSpeed += BASE_MOVEMENT_SPEED*level*0.005f;
}

sf::Vector2f SlimeMiniBoss::attack() {
    return debuff;
}

sf::FloatRect SlimeMiniBoss::getBounds() const {
    return hitBox.getBounds();
}

sf::Vector2f SlimeMiniBoss::getPosition() const {
    return sprite.getPosition();
}