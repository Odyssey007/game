#include "../header/obstacles/object.h"

Object::Object() {
    //preliminaries
    //collisionType = AABB;
    entityType = OBSTACLE;
    //?temporary => set up texture
    obstacle.setFillColor(sf::Color::Yellow);
    obstacle.setSize(sf::Vector2f(75.0f, 100.0f));
    obstacle.setOrigin(sf::Vector2f(75.0f/2.0f, 50.0f));
    //hitbox
    bounds = sf::FloatRect(0, 0, 75, 100);
    hitBox.updateSize(bounds);
    //set initial position
    // initialPosition(sf::Vector2u(0, 0));
}

void Object::render(sf::RenderWindow& window) const {
    window.draw(obstacle);
    //window.draw(hitBox.body);
}

void Object::setInitialPosition(const sf::View& view) {
    sf::FloatRect viewBounds(view.getCenter() - view.getSize() / 2.0f, view.getSize());
    std::pair<int, int> rangeX, rangeY;

    rangeX.first = static_cast<int>(viewBounds.left) + bounds.width/2;
    rangeX.second = static_cast<int>(viewBounds.left + viewBounds.width) - bounds.width/2;

    rangeY.first = static_cast<int>(viewBounds.top) + bounds.height/2;
    rangeY.second = static_cast<int>(viewBounds.top + viewBounds.height) - bounds.height/2;

    sf::Vector2i pos = randomGenerator(rangeX, rangeY);
    
    obstacle.setPosition(pos.x, pos.y);
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

sf::FloatRect Object::getBounds() const {
    return obstacle.getGlobalBounds();
}

sf::Vector2f Object::getPosition() const {
    return hitBox.body.getPosition();
}


//cracker

bool Object::isAlive() const {
    return true;
}

int Object::getState() const {
    return -1;
}

const sf::Vector2f& Object::getVelocity() const {
    static const sf::Vector2f dummyVelocity(0.0f, 0.0f);
    return dummyVelocity;
}

void Object::setVelocity(const sf::Vector2f& velocity) {
    return;
}

void Object::applyMovement() {
    return;
}