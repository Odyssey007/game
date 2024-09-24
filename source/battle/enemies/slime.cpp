#include "../header/battle/enemies/slime.h"

const float BASE_MOVEMENT_SPEED = 175.0f;
const float BASE_SLOW = 0.0f;
const float BASE_DMG = 5.0f;
const float BASE_HP = 70.0f;

Slime::Slime() {
    collisionType = CIRCLE; //update entity-parent
    //update enemy-parent
    movementSpeed = BASE_MOVEMENT_SPEED; 
    debuff = {BASE_DMG, BASE_SLOW}; health = BASE_HP;
    bounds = sf::FloatRect(45, 70, 59, 49);
    //
    sprite.setTexture(*textures["slime"]);
    hitBox.updateSize(bounds);
    sprite.setOrigin(sf::Vector2f((bounds.left + bounds.width/2.0f), (bounds.top + bounds.height/2.0f)));
}

void Slime::update(const sf::Vector2f& target) {
    //slow effects
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
    //animation?
    if (facingRight) {
        sprite.setScale(1.0f, 1.0f); 
    } 
    else {
        sprite.setScale(-1.0f, 1.0f);
    }
    //movement
    if (!hitPlayer) {
        meleeMovement(target);
    } else {
        hitPlayer = false;
    }
    hitBox.followEntity(sprite.getPosition());
}

sf::Vector2f Slime::attack() {
    return debuff;
}

void Slime::checkLvlUp(const size_t level) {
    if (level == 0) return;
    health += BASE_HP*level*0.1f;
    debuff.x += BASE_DMG*level*0.05f;
    movementSpeed += BASE_MOVEMENT_SPEED*level*0.005f;
}

//ENTITY FUNCTIONS

sf::FloatRect Slime::getBounds() const {
    return hitBox.getBounds();
}

sf::Vector2f Slime::getPosition() const {
    return sprite.getPosition();
}