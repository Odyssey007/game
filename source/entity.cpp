#include "../header/entity.h"

//HA HA moment

//these functions aren't used for all child cases
const sf::Vector2f& Entity::getVelocity() const {
    static sf::Vector2f empty(0.0f, 0.0f);
    return empty;
}

void Entity::setVelocity(const sf::Vector2f& v) {
    return;
}

void Entity::applyMovement() {
    return;
}