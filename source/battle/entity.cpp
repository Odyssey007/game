#include "../header/battle/entity.h"

Entity::Entity() {
    alive = true;
}

bool Entity::isAlive() const {
    return alive;
}

//these functions aren't used for some child cases
const sf::Vector2f& Entity::getVelocity() const {
    static sf::Vector2f empty(0.0f, 0.0f);
    return empty;
}

void Entity::setVelocity(const sf::Vector2f& v) {
    return;
}

void Entity::setInitialPosition(const sf::FloatRect& screenBounds) {
    return;
}

void Entity::applyMovement() {
    return;
}