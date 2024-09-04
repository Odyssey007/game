#include "../header/battle/enemies/goblin.h"

Goblin::Goblin() {
    //update parent
    movementSpeed = 250.0f; dmg = 15; slow = 0;
    bounds = sf::FloatRect(8, 2, 25, 40);
    sprite.setTexture(*textures["goblin"]);
    animationSheetDim = sf::Vector2u(4, 1);
    animation = Animation(*textures["goblin"], animationSheetDim, frameDuration);
    //
    collisionType = BOX; enemyType = SLIME;
    hitBox = BoxCollision();
    hitBox.updateSize(bounds);
    sprite.setTextureRect(animation.uvRect);
    sprite.setOrigin(sf::Vector2f((bounds.left + bounds.width/2.0f), (bounds.top + bounds.height/2.0f)));
}

void Goblin::update(const sf::Vector2f& target) {
    if (distance(target, sprite.getPosition()) >= 100.0f) {
        meleeMovement(target);
        isMoving = true;
    } else {
        isMoving = false;
    }
    
    if (isMoving) {
        sf::Vector2f toTarget = target - sprite.getPosition();
        toTarget = normalize(toTarget);
        if (toTarget.x >= 0) {
            facingRight = false;
        } else if (toTarget.x < 0) {
            facingRight = true;
        }
        //
        animation.update(sprite, 0, facingRight, {1.0f, 1.0f});
    } else {
        animation.resetToFirst(sprite, facingRight, {1.0f, 1.0f});
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

sf::Vector2u Goblin::attack() {
    return sf::Vector2u(dmg, slow);
}

void Goblin::checkLvlUp(const size_t level) {
    if (level == 0) return;
    fullHealth += 100*level*0.1f;
    dmg += 15*level*0.05f;
    movementSpeed += 250*level*0.005f;
}

//ENTITY FUNCTIONS

sf::FloatRect Goblin::getBounds() const {
    return hitBox.getBounds();
}

sf::Vector2f Goblin::getPosition() const {
    return hitBox.getPosition();
}

void Goblin::render(sf::RenderWindow& window) const {
    window.draw(sprite);
    // window.draw(hitBox.body);
}