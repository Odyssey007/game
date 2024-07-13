#include "../header/obstacles/object.h"

Object::Object() {
    //preliminaries
    //entityType = OBSTACLE; collisionType = AABB;
    //?temporary => set up texture
    obstacle.setFillColor(sf::Color::Yellow);
    obstacle.setSize(sf::Vector2f(75.0f, 100.0f));
    obstacle.setOrigin(sf::Vector2f(25.0f/2.0f, 50.0f));
    //hitbox
    bounds = sf::FloatRect(0, 0, 75, 100);
    hitBox.updateSize(bounds);
    //set initial position
    initialPosition(sf::Vector2u(800, 400));
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
    if (entity.collisionType == AABB) {
        sf::FloatRect entityBounds = entity.getShape().getGlobalBounds();
        sf::FloatRect objectBounds = this->obstacle.getGlobalBounds();

        sf::Vector2f moveDistance = entity.getVelocity();
        sf::FloatRect nextMovement = entityBounds;
        nextMovement.left += moveDistance.x; 
        nextMovement.top += moveDistance.y;

        if (objectBounds.intersects(nextMovement)) {
            //right
            if (entityBounds.left < objectBounds.left &&
                entityBounds.left + entityBounds.width <= objectBounds.left &&
                entityBounds.top + entityBounds.height > objectBounds.top &&
                entityBounds.top < objectBounds.top + objectBounds.height) {
                    moveDistance.x = 0;
            }

            //left
            if (entityBounds.left > objectBounds.left &&
                entityBounds.left + entityBounds.width > objectBounds.left + objectBounds.width &&
                entityBounds.top + entityBounds.height > objectBounds.top &&
                entityBounds.top < objectBounds.top + objectBounds.height) {
                    moveDistance.x = 0;
            }

            //top
            if (entityBounds.top < objectBounds.top &&
                entityBounds.top + entityBounds.height <= objectBounds.top &&
                entityBounds.left + entityBounds.width > objectBounds.left &&
                entityBounds.left < objectBounds.left + objectBounds.width) {
                    moveDistance.y = 0;
            }

            //bottom
            if (entityBounds.top > objectBounds.top &&
                entityBounds.top + entityBounds.height > objectBounds.top + objectBounds.height &&
                entityBounds.left + entityBounds.width > objectBounds.left &&
                entityBounds.left < objectBounds.left + objectBounds.width) {
                    moveDistance.y = 0;
            }
        }

        entity.setVelocity(moveDistance);
    } else if (entity.collisionType == CIRCLE) {
        sf::FloatRect entityBounds = entity.getShape().getGlobalBounds();
        sf::FloatRect ObjectBounds = this->obstacle.getGlobalBounds();
        
        float radius = entityBounds.width / 2.0f;
        sf::Vector2f currentCenter(entityBounds.left + radius, entityBounds.top + radius);
        
        //next position
        sf::Vector2f moveDistance = entity.getVelocity();
        sf::Vector2f nextCenter = currentCenter + moveDistance;

        sf::Vector2f distanceVector = Collision::calcDistance(ObjectBounds, nextCenter, radius);
        float distance = magnitude(distanceVector);

        if (distance < radius) {
            if (distance != 0) {
                distanceVector /= distance;
            }

            float dot = dotProduct(moveDistance, distanceVector);
            moveDistance -= dot*distanceVector;

            entity.setVelocity(moveDistance);
        }
    }
}