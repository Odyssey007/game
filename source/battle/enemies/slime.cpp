#include "../header/battle/enemies/slime.h"

Slime::Slime() {
    dmg = 5; slow = 0;
    //preliminaries
    collisionType = CIRCLE;
    sprite.setTexture(*textures["slime"]);
    //hit box
    bounds = sf::FloatRect(45, 70, 59, 49);
    hitBox.updateSize(bounds);
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
    //changing direction
    sf::Vector2f toTarget = target - sprite.getPosition();
    toTarget = normalize(toTarget);
    if (toTarget.x >= 0) {
        facingRight = true;
    } else if (toTarget.x < 0) {
        facingRight = false;
    }

    if (facingRight) {
        sprite.setScale(1.0f, 1.0f); 
    } 
    else {
        sprite.setScale(-1.0f, 1.0f);
    }

    //moves
    if (distance(target, sprite.getPosition()) >= 100.0f) {
        meleeMovement(target);
    } 
    hitBox.followEntity(sprite.getPosition());
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
}