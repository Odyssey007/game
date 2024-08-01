#include "../header/obstacles/object.h"

Object::Object() {
    //preliminaries
    //entityType = OBSTACLE; collisionType = AABB;
    //?temporary => set up texture
    obstacle.setFillColor(sf::Color::Yellow);
    obstacle.setSize(sf::Vector2f(75.0f, 100.0f));
    obstacle.setOrigin(sf::Vector2f(75.0f/2.0f, 50.0f));
    //hitbox
    bounds = sf::FloatRect(0, 0, 75, 100);
    hitBox.updateSize(bounds);
    //set initial position
    initialPosition(sf::Vector2u(800, 50));
}

void Object::render(sf::RenderWindow& window) {
    window.draw(obstacle);
    //window.draw(hitBox.body);
}

void Object::initialPosition(const sf::Vector2u& position) {
    obstacle.setPosition(position.x, position.y);
    hitBox.body.setPosition(position.x, position.y);
}

void Object::handleCollision(Entity& entity) {
    sf::FloatRect entityBounds = entity.getBounds();
    sf::Vector2f moveDistance = entity.getVelocity();
    currentBounds = this->obstacle.getGlobalBounds();

    switch (entity.collisionType) {
        case AABB:
            resolveBoxCollision(moveDistance, entityBounds);
            break;
        case CIRCLE:
            resolveCircleCollision(moveDistance, entityBounds);
            break;
    }
    entity.setVelocity(moveDistance);
}

void Object::resolveBoxCollision(sf::Vector2f& velocity, const sf::FloatRect& entityBounds) {
    sf::FloatRect nextMovement = entityBounds;
    nextMovement.left += velocity.x; 
    nextMovement.top += velocity.y;

    if (currentBounds.intersects(nextMovement)) {
        if (entityBounds.left < currentBounds.left && //right
            entityBounds.left + entityBounds.width <= currentBounds.left &&
            entityBounds.top + entityBounds.height > currentBounds.top &&
            entityBounds.top < currentBounds.top + currentBounds.height) {
                velocity.x = 0;
        } else if (entityBounds.left > currentBounds.left && //left
            entityBounds.left + entityBounds.width > currentBounds.left + currentBounds.width &&
            entityBounds.top + entityBounds.height > currentBounds.top &&
            entityBounds.top < currentBounds.top + currentBounds.height) {
                velocity.x = 0;
        } else if (entityBounds.top < currentBounds.top && //top
            entityBounds.top + entityBounds.height <= currentBounds.top &&
            entityBounds.left + entityBounds.width > currentBounds.left &&
            entityBounds.left < currentBounds.left + currentBounds.width) {
                velocity.y = 0;
        } else if (entityBounds.top > currentBounds.top && //bottom
            entityBounds.top + entityBounds.height > currentBounds.top + currentBounds.height &&
            entityBounds.left + entityBounds.width > currentBounds.left &&
            entityBounds.left < currentBounds.left + currentBounds.width) {
                velocity.y = 0;
        }
    }
}

void Object::resolveCircleCollision(sf::Vector2f& velocity, const sf::FloatRect& entityBounds) {
    float radius = entityBounds.width / 2.0f;
    sf::Vector2f currentCenter(entityBounds.left + radius, entityBounds.top + radius);
    
    sf::Vector2f nextCenter = currentCenter + velocity; 
    sf::Vector2f distanceVector = Collision::calcDistance(currentBounds, nextCenter, radius);
    float distance = magnitude(distanceVector);

    if (distance < radius) {
        if (distance != 0) distanceVector /= distance;

        float overlap = radius - distance;
        sf::Vector2f correction = distanceVector * overlap;
        nextCenter += correction;
        velocity = nextCenter - currentCenter;    
    }
}
