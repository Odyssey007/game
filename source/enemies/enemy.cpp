#include "../header/enemies/enemy.h"

Enemy::Enemy() {
    //preliminaries
    health = 100;
    entityType = ENEMY; alive = true; currentAbility = 0;
    loadTexture("slime", "assets/enemies/slime.png");
    loadTexture("goblin", "assets/enemies/goblinSheet.png");
    //movement set up
    movementSpeed = 150; baseDamage = 5;
    bestDirection = sf::Vector2f(0.0f, 0.0f);
    generateDirections();
}

void Enemy::loadTexture(const std::string& name, const std::string& filePath) {
    auto texture = std::make_shared<sf::Texture>(); 
    if (texture->loadFromFile(filePath)) {
        textures[name] = texture;
    } else {
        throw std::runtime_error("Failed to load enemy texture");
    }
}

//generates all the directions of possible movement
void Enemy::generateDirections(int numDirections) {
    const float zeroThreshold = 1e-6; //to stop floating point precision error
    directions.clear();
    for (int i = 0; i < numDirections; i++) {
        float angle = 2 * M_PI * i / numDirections;
        float x = std::cos(angle);
        float y = std::sin(angle);
        if (std::abs(x) < zeroThreshold) x = 0;
        if (std::abs(y) < zeroThreshold) y = 0;
        directions.push_back(sf::Vector2f(x, y));
    }
}

void Enemy::meleeMovement(const sf::Vector2f& target) {
    sf::Vector2f toTarget = target - sprite.getPosition();
    toTarget = normalize(toTarget);
    //finds the optimal direction toward target 
    float maxDot = -1.0f;
    for (int i = 0; i < 32; i++) {
        float dot = dotProduct(directions[i], toTarget);
        if (dot > maxDot) {
            maxDot = dot;
            bestDirection = directions[i];
        }
    }
    //separation force from neighbors
    
    //move
    moveDistance = bestDirection*static_cast<float>(movementSpeed)*DeltaTime::getInstance()->getDeltaTime();
}

//ENTITY FUNCTIONS

void Enemy::setInitialPosition(const sf::FloatRect& screenBounds) {
    //pick the side of the screen to spawn in
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> distribute(1, 4);

    std::pair<int, int> rangeX, rangeY;
    switch (distribute(gen)) {
        case 1: //top
            rangeX = {static_cast<int>(screenBounds.left), static_cast<int>(screenBounds.left + screenBounds.width)};
            rangeY = {static_cast<int>(screenBounds.top) - 150, static_cast<int>(screenBounds.top) - 100};
            break;
        case 2: //bottom --sd
            rangeX = {static_cast<int>(screenBounds.left), static_cast<int>(screenBounds.left + screenBounds.width)};
            rangeY = {static_cast<int>(screenBounds.top + screenBounds.height) + 100, static_cast<int>(screenBounds.top + screenBounds.height) + 150};
            break;
        case 3: //left -- sd
            rangeX = {static_cast<int>(screenBounds.left) - 150, static_cast<int>(screenBounds.left) - 100};
            rangeY = {static_cast<int>(screenBounds.top), static_cast<int>(screenBounds.top + screenBounds.height)};
            break;
        case 4: //right
            rangeX = {static_cast<int>(screenBounds.left + screenBounds.width) + 100, static_cast<int>(screenBounds.left + screenBounds.width) + 150};
            rangeY = {static_cast<int>(screenBounds.top), static_cast<int>(screenBounds.top + screenBounds.height)};
            break;
    }
    sf::Vector2i spawnPosition = randomGenerator(rangeX, rangeY);

    sprite.setPosition(spawnPosition.x, spawnPosition.y);
}

//ENTITY FUNCTIONS

bool Enemy::isAlive() const {
    return alive;
}

const sf::Vector2f& Enemy::getVelocity() const {
    return moveDistance;
}

void Enemy::setVelocity(const sf::Vector2f& velocity) {
    moveDistance = velocity;
}


void Enemy::applyMovement() {
    sprite.move(moveDistance);
    moveDistance = sf::Vector2f(0.0f, 0.0f);
}


void Enemy::handleCollision(Entity& entity) {
    if (this->collisionType == BOX && entity.collisionType == BOX) {
        boxOverlap(entity, *this);
        return;
    }
    if (this->collisionType == CIRCLE && entity.collisionType == CIRCLE) {
        circleOverlap(entity, *this);
        return;
    }
    if (this->collisionType == BOX && entity.collisionType == CIRCLE) {
        boxCircleOverlap(*this, entity);
    } else {
        boxCircleOverlap(entity, *this);
    }
}

void Enemy::circleOverlap(Entity& entity1, Entity& entity2) {
    sf::Vector2f position1 = entity1.getPosition();
    sf::Vector2f position2 = entity2.getPosition();

    float minDistance = (entity1.getBounds().width / 2.0f) + (entity2.getBounds().width / 2.0f);
    float dist = distance(position1, position2);
    float overlap = minDistance - dist;

    if (dist > 0.0f && overlap > 0.0f) {;
        sf::Vector2f direction = normalize(position2 - position1);
        sf::Vector2f correction = direction * (overlap * 0.5f); 

        entity1.setVelocity(entity1.getVelocity() - correction);
        entity2.setVelocity(entity2.getVelocity() + correction);
    }
}

void Enemy::boxOverlap(Entity& entity1, Entity& entity2) {
    sf::FloatRect rect1 = entity1.getBounds();
    sf::FloatRect rect2 = entity2.getBounds();

    float overlapX = std::min(rect1.left + rect1.width, rect2.left + rect2.width) - std::max(rect1.left, rect2.left);
    float overlapY = std::min(rect1.top + rect1.height, rect2.top + rect2.height) - std::max(rect1.top, rect2.top);

    sf::Vector2f velocity1 = entity1.getVelocity();
    sf::Vector2f velocity2 = entity2.getVelocity();

    if (overlapX < overlapY) {
        //x-axis
        if (rect1.left < rect2.left) {
            velocity1.x -= overlapX / 2.0f;
            velocity2.x += overlapX / 2.0f;
        } else {
            velocity1.x += overlapX / 2.0f;
            velocity2.x -= overlapX / 2.0f;
        }
    } else {
        //y-axis
        if (rect1.top < rect2.top) {
            velocity1.y -= overlapY / 2.0f;
            velocity2.y += overlapY / 2.0f;
        } else {
            velocity1.y += overlapY / 2.0f;
            velocity2.y -= overlapY / 2.0f;
        }
    }
    entity1.setVelocity(velocity1);
    entity2.setVelocity(velocity2);
}

void Enemy::boxCircleOverlap(Entity& box, Entity& circle) {
    sf::FloatRect boxBounds = box.getBounds();
    sf::Vector2f circleCenter = circle.getPosition();
    float circleRadius = circle.getBounds().width / 2.0f;

    // Calculate the separation vector between the box and the circle
    sf::Vector2f separationVec = Collision::calcDistance(boxBounds, circleCenter, circleRadius);    
    float distance = magnitude(separationVec);

    if (distance < circleRadius) {
        sf::Vector2f direction = normalize(separationVec);
        float correction = circleRadius - distance;

        // Apply a fraction of the correction as position adjustment to reduce jitter
        const float positionCorrectionFactor = 0.3f; // Lower factor to reduce pushback
        sf::Vector2f positionAdjustment = direction * (correction * positionCorrectionFactor);

        // Apply the position adjustment directly to prevent fast pushback
        circleCenter += positionAdjustment;

        // Optionally apply a small velocity adjustment
        const float velocityCorrectionFactor = 0.1f; // Smaller correction to avoid jitter
        sf::Vector2f velocityAdjustment = direction * (correction * velocityCorrectionFactor);

        sf::Vector2f circleVelocity = circle.getVelocity();
        circleVelocity += velocityAdjustment;

        sf::Vector2f boxVelocity = box.getVelocity();
        boxVelocity -= velocityAdjustment;

        // Apply damping to smooth out any residual jitter
        const float dampingFactor = 0.9f;
        circleVelocity *= dampingFactor;
        boxVelocity *= dampingFactor;

        // Update velocities
        circle.setVelocity(circleVelocity);
        box.setVelocity(boxVelocity);
    }
}
