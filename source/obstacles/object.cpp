#include "../header/obstacles/object.h"

Object::Object() {
    //preliminaries
    entityType = OBSTACLE; collisionType = BOX;
    loadTexture("assets/obstacles/pillar1.png");
    loadTexture("assets/obstacles/pillar2.png");
    sprite.setTexture(*textures[1]); 
    /*
    4. type
    1. scale
    2. rotation
    3. reflection
    */

    sprite.setScale(2.0f, 2.0f);
    bounds = sprite.getGlobalBounds();
    sprite.setOrigin(sf::Vector2f((bounds.left + bounds.width/2.0), (bounds.top + bounds.height/2.0f)));
}

int randomGen() {
    return rand() % 4;
}

void Object::loadTexture(const std::string& filePath) {
    auto texture = std::make_shared<sf::Texture>(); 
    if (texture->loadFromFile(filePath)) {
        textures.push_back(texture);
    } else {
        throw std::runtime_error("Failed to load enemy texture");
    }
}



void Object::render(sf::RenderWindow& window) const {
    window.draw(sprite);
}

void Object::setInitialPosition(const sf::FloatRect& screenBounds) {
    std::pair<int, int> rangeX, rangeY;

    rangeX.first = static_cast<int>(screenBounds.left) + bounds.width/2;
    rangeX.second = static_cast<int>(screenBounds.left + screenBounds.width) - bounds.width/2;

    rangeY.first = static_cast<int>(screenBounds.top) + bounds.height/2;
    rangeY.second = static_cast<int>(screenBounds.top + screenBounds.height) - bounds.height/2;

    sf::Vector2i pos = randomGenerator(rangeX, rangeY);
    
    sprite.setPosition(pos.x, pos.y);
}

void Object::handleCollision(Entity& entity) {
    sf::FloatRect entityBounds = entity.getBounds();
    sf::Vector2f moveDistance = entity.getVelocity();
    currentBounds = this->sprite.getGlobalBounds();

    switch (entity.collisionType) {
        case BOX:
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

    if (!currentBounds.intersects(nextMovement)) return;

    bool horizontalIntersect = entityBounds.left + entityBounds.width > currentBounds.left &&
                               entityBounds.left < currentBounds.left + currentBounds.width;
    bool verticalIntersect = entityBounds.top + entityBounds.height > currentBounds.top &&
                             entityBounds.top < currentBounds.top + currentBounds.height;

    if (horizontalIntersect) {
        if (entityBounds.top < currentBounds.top && 
            entityBounds.top + entityBounds.height <= currentBounds.top) {
            velocity.y = 0; //top
        } else if (entityBounds.top > currentBounds.top + currentBounds.height) {
            velocity.y = 0; //bottom
        }
    }
    if (verticalIntersect) {
        if (entityBounds.left < currentBounds.left && 
            entityBounds.left + entityBounds.width <= currentBounds.left) {
            velocity.x = 0; //right
        } else if (entityBounds.left > currentBounds.left + currentBounds.width) {
            velocity.x = 0; //left
        }
    }
}

void Object::resolveCircleCollision(sf::Vector2f& velocity, const sf::FloatRect& entityBounds) {
    float radius = entityBounds.width / 2.0f;
    sf::Vector2f currentCenter(entityBounds.left + radius, entityBounds.top + radius);
    
    sf::Vector2f nextCenter = currentCenter + velocity; 
    sf::Vector2f distanceVector = Collision::calcDistance(currentBounds, nextCenter, radius);
    float distanceSquared = distanceVector.x * distanceVector.x + distanceVector.y * distanceVector.y;
    float radiusSquared = radius * radius;

    if (distanceSquared < radiusSquared) {
        float distance = std::sqrt(distanceSquared);
        if (distance != 0) {
            distanceVector /= distance;
        }

        float overlap = radius - distance;
        sf::Vector2f correction = distanceVector * overlap;
        nextCenter += correction;
        velocity = nextCenter - currentCenter;    
    }
}

sf::FloatRect Object::getBounds() const {
    return sprite.getGlobalBounds();
}

sf::Vector2f Object::getPosition() const {
    return sprite.getPosition();
}


//cracker

bool Object::isAlive() const {
    return true;
}