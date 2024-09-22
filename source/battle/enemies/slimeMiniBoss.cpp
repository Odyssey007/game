#include "../header/battle/enemies/slimeMiniBoss.h"

SlimeMiniBoss::SlimeMiniBoss() : 
    //leap buffers
    leapingSpeed(5.5f), leaping(false), chargeTimer(0.35f), needToRecover(false), recoveryTimer(0.35f),
    //leap distance
    leapDistance(275.0f), totalLeapDistance(0.0f)
{
    debuff = {10, 0}; health = 300; fullHealth = 250;
    //preliminaries
    collisionType = CIRCLE;
    sprite.setTexture(*textures["slime"]);
    //hit box
    bounds = sf::FloatRect(39, 65, 75, 62);
    hitBox.updateSize(bounds);
    //set origin and position
    scale = 1.3f;
    sprite.setScale(scale, scale);
    sprite.setColor(sf::Color(236, 59, 59));
    sprite.setOrigin(sf::Vector2f((bounds.left + bounds.width/2.0f), (bounds.top + bounds.height/2.0f)));
}

void SlimeMiniBoss::update(const sf::Vector2f& target) {
    if (isSlowed) {
        effectDuration -= DeltaTime::getInstance()->getDeltaTime();
    }
    if (isSlowed && effectDuration <= 0) {
        isSlowed = false;
        movementSpeed = 150.0f;
        effectDuration = 1.0f;
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
        totalLeapDistance = 0.0f;
        //start buffer
        leaping = false;
        //end buffer
        needToRecover = true;
        recoveryTimer = 0.35f;
    }
}

void SlimeMiniBoss::checkLvlUp(const size_t level) {
    if (level == 0) return;
    fullHealth += 100*level*0.1f;
    debuff.x += 15*level*0.05f;
    movementSpeed += 250*level*0.005f;
}

sf::Vector2u SlimeMiniBoss::attack() {
    return debuff;
}

sf::FloatRect SlimeMiniBoss::getBounds() const {
    return hitBox.getBounds();
}

sf::Vector2f SlimeMiniBoss::getPosition() const {
    return sprite.getPosition();
}

void SlimeMiniBoss::render(sf::RenderWindow& window) const {
    if (alive) {
        window.draw(sprite);
    }
}