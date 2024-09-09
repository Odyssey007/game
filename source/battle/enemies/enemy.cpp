#include "../header/battle/enemies/enemy.h"

Enemy::Enemy() :
    //animation
    animationSheetDim(sf::Vector2u(0, 0)), frameDuration(0.18f),
    //attributes
    fullHealth(100), movementSpeed(150.0f), baseDamage(10), attackCooldown(1.5f),
    //movement
    totalDirections(32), bestDirection(sf::Vector2f(0.0f, 0.0f)), 
    moveDistance(sf::Vector2f(0.0f, 0.0f)), bounds(sf::FloatRect(0.0f, 0.0f, 0.0f, 0.0f))
{
    //update parent
    entityType = ENEMY;
    //
    loadTexture("slime", "assets/enemies/slime.png");
    loadTexture("goblin", "assets/enemies/goblinSheet.png");
    generateDirections();
}

void Enemy::loadTexture(const std::string& name, const std::string& filePath) {
    auto texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile(filePath)) {
        throw std::runtime_error("Failed to load enemy texture: " + filePath);
    }
    textures.emplace(name, std::move(texture));
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
    sf::Vector2f rawToTarget = target - this->getPosition();
    sf::Vector2f toTarget = normalize(rawToTarget);
    sf::Vector2f whereBlocked = toTarget;
    //determines best direction towards player
    float maxDot = -1.0f;
    bestDirection = directions[0]; //default direction
    for (int i = 0; i < totalDirections; i++) {
        float dot = dotProduct(directions[i], toTarget);
        if (dot > maxDot) {
            maxDot = dot;
            bestDirection = directions[i];
        }
    }
    //check if path is blocked by neighbor
    bool isCircling = false;
    float speed = movementSpeed;
    if (isPathBlocked(target, whereBlocked)) {
        if (magnitude(rawToTarget) < 145.0f) { //hovers around target
            if (!isCircling) {
                bestDirection = sf::Vector2f(-toTarget.y, toTarget.x); //perpendicular to target
                isCircling = true;
            }
            speed /= 1.5f;
        } else if (magnitude(whereBlocked) < 200.0f) { //avoid blocked paths
            if (!isCircling) {
                avoidBlocking(toTarget, whereBlocked);
                speed /= 1.5f;
            }
        }
    } else {
        isCircling = false;
    }
    //update next movement
    moveDistance = bestDirection*speed*DeltaTime::getInstance()->getDeltaTime();
}


//check if path blocked; if so, updates whereBlocked 
bool Enemy::isPathBlocked(const sf::Vector2f& target, sf::Vector2f& whereBlocked) {
    bool pathBlocked = false;
    for (Entity* neighbor : neighbors) {
        if (neighbor != this) { //stop self neighboring
            //create a line segment from cur to future position
            sf::Vector2f myPos = this->getPosition();
            sf::Vector2f playerPos = target;
            sf::FloatRect neighborBounds = neighbor->getBounds();
            if (moveDistance.x >= 0.0f) { //stops line from meeting target center
                playerPos.x = target.x + 100.0f; //right
            } else {
                playerPos.x = target.x - 100.0f; //left
            }
            sf::FloatRect pathBounds(std::min(myPos.x, playerPos.x), std::min(myPos.y, playerPos.y),
                                     std::abs(myPos.x - playerPos.x), std::abs(myPos.y - playerPos.y));
            pathBounds.left -= neighborBounds.width/2;
            pathBounds.top -= neighborBounds.height/2;
            pathBounds.width += neighborBounds.width;
            pathBounds.height += neighborBounds.height;
            //check if path collides with neighbor
            if ((neighbor->collisionType == BOX && BoxCollision::checkCollision(pathBounds, neighborBounds)) ||
            (neighbor->collisionType == CIRCLE && Collision::checkCollision(pathBounds, neighborBounds))) {
                pathBlocked = true;
                whereBlocked = neighbor->getPosition() - myPos;
                // whereBlocked.x = abs(whereBlocked.x); whereBlocked.y = abs(whereBlocked.y);
                break;
            }
        }
    }
    return pathBlocked;
}

//best direction to avoid blocked path and still move towards target
void Enemy::avoidBlocking(const sf::Vector2f& toTarget, const sf::Vector2f& whereBlocked) {
    float maxDot = -std::numeric_limits<float>::max();
    for (const auto& direction : directions) {
        float dotToBlocked = dotProduct(direction, whereBlocked);
        //get direction away from whereBlocked
        if (dotToBlocked < 0.0f) {
            float dotToTarget = dotProduct(direction, toTarget);
            if (dotToTarget > maxDot) {
                maxDot = dotToTarget;
                bestDirection = direction;
            }
        }
    }
}

float Enemy::getAttackCooldown() const {
    return attackCooldown;
}

void Enemy::setNeighbors(const std::vector<Entity*>& newNeighbors) {
    neighbors.clear();
    neighbors.insert(neighbors.end(), newNeighbors.begin(), newNeighbors.end());
}

void Enemy::checkAlive() {
    if (health <= 0) {
        alive = false;
    }
}

float Enemy::getAttackTimer() const {
    return attackTimer.getElapsedTime().asSeconds();
}

void Enemy::restartAttackTimer() {
    attackTimer.restart();
}

//x = hp | y = ms
void Enemy::takeDebuff(sf::Vector2u debuff, bool stun) {
    health -= debuff.x;
    movementSpeed -= debuff.y; //!will not work with stun
}

void Enemy::spawn(const size_t level, const sf::FloatRect& screenBounds) {
    this->alive = true; 
    checkLvlUp(level);
    health = fullHealth;
    setInitialPosition(screenBounds);
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
    EntityType otherEntity = entity.entityType;
    if (otherEntity == PLAYER || otherEntity == OBSTACLE || 
        otherEntity == EXP) return;
    //
    if (otherEntity == ENEMY) {
        handleEnemyCollision(entity);
    } else if (otherEntity == COLLISION_ABILITY || otherEntity == TIMED_ABILITY) {
        handleAbilityCollision(entity);
    }
}

void Enemy::handleAbilityCollision(Entity& entity) {
    Ability* ability = dynamic_cast<Ability*>(&entity);
    if (ability->getBufferTime() >= 0.05f) {
        takeDebuff(ability->hitEnemy(), ability->stun);
        ability->restartBufferTime();
    }
}

void Enemy::handleEnemyCollision(Entity& entity) {
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

    sf::Vector2f separationVec = Collision::calcDistance(boxBounds, circleCenter, circleRadius);    
    float distance = magnitude(separationVec);

    if (distance < circleRadius) {
        sf::Vector2f direction = normalize(separationVec);
        float correction = circleRadius - distance;
        //reduce pushback
        const float positionCorrectionFactor = 0.3f;
        sf::Vector2f positionAdjustment = direction * (correction * positionCorrectionFactor);
        circleCenter += positionAdjustment;
        //to reduce jitter
        const float velocityCorrectionFactor = 0.1f; 
        sf::Vector2f velocityAdjustment = direction * (correction * velocityCorrectionFactor);
        //set new 
        sf::Vector2f circleVelocity = circle.getVelocity();
        circleVelocity += velocityAdjustment;
        sf::Vector2f boxVelocity = box.getVelocity();
        boxVelocity -= velocityAdjustment;
        // dampening for residual jitter
        const float dampingFactor = 0.9f;
        circleVelocity *= dampingFactor;
        boxVelocity *= dampingFactor;

        circle.setVelocity(circleVelocity);
        box.setVelocity(boxVelocity);
    }
}