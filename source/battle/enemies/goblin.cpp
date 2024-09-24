#include "../header/battle/enemies/goblin.h"

const float BASE_MOVEMENT_SPEED = 215.0f;
const float BASE_SLOW = 0.0f; //done in %
const float BASE_DMG = 10.0f;
const float BASE_HP = 45.0f;

Goblin::Goblin() {
    collisionType = BOX; //update entity-parent
    //update enemy-parent
    movementSpeed = BASE_MOVEMENT_SPEED; 
    debuff = {BASE_DMG, BASE_SLOW}; health = BASE_HP;
    bounds = sf::FloatRect(8, 2, 25, 40);
    //
    sprite.setTexture(*textures["goblin"]);
    animationSheetDim = sf::Vector2u(4, 1);
    animation = Animation(*textures["goblin"], animationSheetDim, frameDuration);
    hitBox.updateSize(bounds);
    sprite.setTextureRect(animation.uvRect);
    sprite.setOrigin(sf::Vector2f((bounds.left + bounds.width/2.0f), (bounds.top + bounds.height/2.0f)));
}

void Goblin::update(const sf::Vector2f& target) {
    //slow effects
    if (isSlowed) {
        slowDuration -= DeltaTime::getInstance()->getDeltaTime();
    }
    if (isSlowed && slowDuration <= 0) {
        isSlowed = false;
        slowDuration = 1.0f;
        movementSpeed = BASE_MOVEMENT_SPEED;
    }
    //facing direction
    sf::Vector2f toTarget = target - sprite.getPosition();
    toTarget = normalize(toTarget);
    if (toTarget.x >= 0) {
        facingRight = false;
    } else if (toTarget.x < 0) {
        facingRight = true;
    }
    //animation
    if (isMoving) {
        animation.update(sprite, 0, facingRight, {1.0f, 1.0f});
    } else {
        animation.resetToFirst(sprite, facingRight, {1.0f, 1.0f});
    }
    //movement
    if (!hitPlayer) {
        meleeMovement(target);
        isMoving = true;
    } else {
        hitPlayer = false;
    }
    hitBox.followEntity(sprite.getPosition());
}

void Goblin::isFacingRight() {
    if (moveDistance.x >= 0.0f) {
        facingRight = false;
    } else {
        facingRight = true;
    }
}

sf::Vector2f Goblin::attack() {
    return debuff;
}

void Goblin::checkLvlUp(const size_t level) {
    if (level == 0) return;
    health += BASE_HP*level*0.1f;
    debuff.x += BASE_DMG*level*0.05f;
    movementSpeed += BASE_MOVEMENT_SPEED*level*0.005f;
}

//ENTITY FUNCTIONS

sf::FloatRect Goblin::getBounds() const {
    return hitBox.getBounds();
}

sf::Vector2f Goblin::getPosition() const {
    return sprite.getPosition();
}