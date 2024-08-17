#include "../header/battle/enemies/goblin.h"

Goblin::Goblin() {
    movementSpeed = 250;
    //preliminaries
    enemyType = SLIME; collisionType = BOX;
    animationSheetDim = sf::Vector2u(4, 1); frameDuration = 0.18f; 
    sprite.setTexture(*textures["goblin"]);
    animation = Animation(*textures["goblin"], animationSheetDim, frameDuration);
    sprite.setTextureRect(animation.uvRect);
    hitBox = BoxCollision();
    bounds = sf::FloatRect(8, 2, 25, 40);
    hitBox.updateSize(bounds);
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
        animation.update(sprite, 0, facingRight, {1.0f, 1.0f});
    } else {
        animation.resetToFirst(sprite, facingRight, {1.0f, 1.0f});
    }
    hitBox.followEntity(sprite.getPosition());
}

void Goblin::attacks() {
    return;
}

void Goblin::playerContact(Player& player, Entity& slime) {

}

//ENTITY FUNCTIONS

sf::FloatRect Goblin::getBounds() const {
    return hitBox.body.getGlobalBounds();
}

sf::Vector2f Goblin::getPosition() const {
    return hitBox.body.getPosition();
}

void Goblin::render(sf::RenderWindow& window) const {
    window.draw(sprite);
    window.draw(hitBox.body);
}