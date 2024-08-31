#include "../header/battle/obstacles/pillar.h"

Pillar::Pillar() {
    //preliminaries
    entityType = OBSTACLE; collisionType = BOX;
    loadTexture("assets/obstacles/pillar1.png");
    loadTexture("assets/obstacles/pillar2.png");
    selectProperties();
    bounds = sprite.getGlobalBounds();
    sprite.setOrigin(sf::Vector2f((bounds.left + bounds.width/2.0f), (bounds.top + bounds.height/2.0f)));
}

void Pillar::loadTexture(const std::string& filePath) {
    auto texture = std::make_unique<sf::Texture>(); 
    if (!texture->loadFromFile(filePath)) {
        throw std::runtime_error("Failed to load enemy texture");  
    } 
    textures.emplace_back(std::move(texture));
}

void Pillar::selectProperties() {
    int type = attributeSelectorI(0, 1);
    sprite.setTexture(*textures[type]);
    int angle = rotationAngle();
    sprite.rotate(angle);
    float scale = attributeSelectorF(1.5f, 2.5f);
    sprite.setScale(scale, scale);
    alive = (attributeSelectorI(10, 11) != 11);
}

int Pillar::attributeSelectorI(int first, int second) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(first, second);
    return dis(gen);
}

float Pillar::attributeSelectorF(float first, float second) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(first, second);
    return dis(gen);
}

int Pillar::rotationAngle() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 4);
    int randomIndex = dis(gen);
    //picks an int between these
    int angles[] = {0, 90, 180, 270, 360};
    return angles[randomIndex];
}

void Pillar::setInitialPosition(const sf::FloatRect& screenBounds) {
    std::pair<int, int> rangeX, rangeY;

    rangeX.first = static_cast<int>(screenBounds.left) + bounds.width/2;
    rangeX.second = static_cast<int>(screenBounds.left + screenBounds.width) - bounds.width/2;

    rangeY.first = static_cast<int>(screenBounds.top) + bounds.height/2;
    rangeY.second = static_cast<int>(screenBounds.top + screenBounds.height) - bounds.height/2;

    sf::Vector2i pos = randomGenerator(rangeX, rangeY);
    
    sprite.setPosition(pos.x, pos.y);
}

void Pillar::respawn(const sf::FloatRect& screenBounds) {
    sf::FloatRect currentBounds = this->getBounds();
    if (!screenBounds.intersects(currentBounds)) {
        if (!timerRunning) {
            timer.restart();
            timerRunning = true;
        }
        if (timer.getElapsedTime().asSeconds() <= 3.0f) {
            return;
        }
        timerRunning = false;
        if (attributeSelectorI(10, 11) == 11) { // 10 - true | 11 - false
            alive = false;
            return;
        } 
        alive = true;
        
        this->selectProperties();
        this->respawnPosition(screenBounds);
    } else if (timerRunning) {
        timer.restart();
        timerRunning = false;
    }
}

void Pillar::respawnPosition(const sf::FloatRect& screenBounds) {
    std::pair<int, int> rangeX, rangeY;
    int offset = 350; 
    int side = attributeSelectorI(0, 3); 
    switch (side) {
        case 0: //left
            rangeX.first = static_cast<int>(screenBounds.left) - bounds.width - offset;
            rangeX.second = static_cast<int>(screenBounds.left) - offset;
            rangeY.first = static_cast<int>(screenBounds.top) - bounds.height - offset;
            rangeY.second = static_cast<int>(screenBounds.top + screenBounds.height + offset);
            break;
        case 1: //right
            rangeX.first = static_cast<int>(screenBounds.left + screenBounds.width) + offset;
            rangeX.second = static_cast<int>(screenBounds.left + screenBounds.width) + bounds.width + offset;
            rangeY.first = static_cast<int>(screenBounds.top) - bounds.height - offset;
            rangeY.second = static_cast<int>(screenBounds.top + screenBounds.height + offset);
            break;
        case 2: //top
            rangeX.first = static_cast<int>(screenBounds.left) - bounds.width - offset;
            rangeX.second = static_cast<int>(screenBounds.left + screenBounds.width + offset);
            rangeY.first = static_cast<int>(screenBounds.top) - bounds.height - offset;
            rangeY.second = static_cast<int>(screenBounds.top) - offset;
            break;
        case 3: //bottom
            rangeX.first = static_cast<int>(screenBounds.left) - bounds.width - offset;
            rangeX.second = static_cast<int>(screenBounds.left + screenBounds.width + offset);
            rangeY.first = static_cast<int>(screenBounds.top + screenBounds.height) + offset;
            rangeY.second = static_cast<int>(screenBounds.top + screenBounds.height) + bounds.height + offset;
            break;
    }
    sf::Vector2i pos = randomGenerator(rangeX, rangeY);
    sprite.setPosition(pos.x, pos.y);
}

void Pillar::handleCollision(Entity& entity) {
    EntityType otherEntity = entity.entityType;
    if (otherEntity == PLAYER || otherEntity == ENEMY) {
        stopEntities(entity);
    } else if (otherEntity == OBSTACLE) {
        return;
    } else if (otherEntity == BLAST) {
        return;
    }
}

void Pillar::stopEntities(Entity& entity) {
    sf::FloatRect entityBounds = entity.getBounds();
    sf::Vector2f moveDistance = entity.getVelocity();
    currentBounds = this->sprite.getGlobalBounds();

    bool hit;
    switch (entity.collisionType) {
        case BOX:
            hit = resolveBoxCollision(moveDistance, entityBounds);
            break;
        case CIRCLE:
            hit = resolveCircleCollision(moveDistance, entityBounds);
            break;
    }
    if (hit) {
        entity.setVelocity(moveDistance);
        entity.handleCollision(*this);
    }
}

bool Pillar::resolveBoxCollision(sf::Vector2f& velocity, const sf::FloatRect& entityBounds) {
    sf::FloatRect nextMovement = entityBounds;
    nextMovement.left += velocity.x; 
    nextMovement.top += velocity.y;

    if (!currentBounds.intersects(nextMovement)) return false;

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
    return true;
}

bool Pillar::resolveCircleCollision(sf::Vector2f& velocity, const sf::FloatRect& entityBounds) {
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
        return true;
    }
    return false;
}

sf::FloatRect Pillar::getBounds() const {
    return sprite.getGlobalBounds();
}

sf::Vector2f Pillar::getPosition() const {
    return sprite.getPosition();
}

void Pillar::render(sf::RenderWindow& window) const {
    window.draw(sprite);
}

//!MAKE A FUCNTION THAT RETURN ALIVE