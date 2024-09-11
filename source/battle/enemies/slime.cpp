#include "../header/battle/enemies/slime.h"

Slime::Slime() :
    //ability
    firstAttack(true),
    //leap buffers
    leaping(false), chargeTimer(0.35f), needToRecover(false), recoveryTimer(0.35f),
    //leap distance
    leapDistance(150.0f), totalLeapDistance(0.0f)
{
    dmg = 5; slow = 0;
    //preliminaries
    enemyType = SLIME; collisionType = CIRCLE;
    sprite.setTexture(*textures["slime"]);
    //hit box
    hitBox = CircleCollision();
    bounds = sf::FloatRect(45, 70, 59, 49);
    hitBox.updateSize(bounds);
    //hitBoxBody = std::make_shared<sf::CircleShape>(hitBox.body);
    //set origin and position
    sprite.setOrigin(sf::Vector2f((bounds.left + bounds.width/2.0f), (bounds.top + bounds.height/2.0f)));
}

void Slime::update(const sf::Vector2f& target) {
    if (isSlowed) {
        effectDuration -= DeltaTime::getInstance()->getDeltaTime();
    }
    if (isSlowed && effectDuration <= 0) {
        isSlowed = false;
        movementSpeed = 150.0f;
        effectDuration = 1.0f;
    }
    // Check if recovery buffer is needed for attack  
    if (needToRecover) {
        if (recoveryTimer > 0) {
            recoveryTimer -= DeltaTime::getInstance()->getDeltaTime();
            return;
        }
        needToRecover = false;
    }

    float canLeap = 100.0f;

    //moves
    if (distance(target, sprite.getPosition()) >= canLeap && !leaping) {
        meleeMovement(target);
    } else { //attacks
        normalAttack();
    }
    //!problem with hitbox when leap attack it doesn't track for a sec
    hitBox.followEntity(sprite.getPosition());
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
        sprite.move(move);
        totalLeapDistance += magnitude(move);
    } else if (leaping) {
        totalLeapDistance = 0.0f;
        //start buffer
        leaping = false;
        chargeTimer = 0.35f;
        //end buffer
        needToRecover = true;
        recoveryTimer = 0.35f;
        //
        firstAttack = false;
    }
}

sf::Vector2u Slime::attack() {
    return sf::Vector2u(dmg, slow);
}

void Slime::checkLvlUp(const size_t level) {
    if (level == 0) return;
    fullHealth += 100*level*0.1f;
    dmg += 15*level*0.05f;
    movementSpeed += 250*level*0.005f;
}

//ENTITY FUNCTIONS

sf::FloatRect Slime::getBounds() const {
    return hitBox.getBounds();
}

sf::Vector2f Slime::getPosition() const {
    return sprite.getPosition();
}

void Slime::render(sf::RenderWindow& window) const {
    window.draw(sprite);
    // window.draw(hitBox.body);
}