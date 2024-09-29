#include "../header/battle/enemies/goblinBoss/bulletSpray.h"

const float ABILITY_COOLDOWN = 8.0f;
const float ABILITY_DURATION = 5.0f;
const float FIRE_COOLDOWN = 0.07f;

BulletSprayPool::BulletSprayPool() :
    alive(false), numShots(244), 
    shouldCast(true), abilityCooldown(ABILITY_COOLDOWN),
    isFiring(false), abilityDuration(ABILITY_DURATION),
    //starting pos
    angleOffset(0.0f), angleIncrement(M_PI/8),
    maxNumPos(12), curNumPos(0), radius(75.0f)
{
    for (size_t i = 0; i < numShots; i++) {
        shotsPool.emplace_back(std::make_unique<BulletSpray>());
    }
}

bool BulletSprayPool::isAlive() const {
    return alive;
}

bool BulletSprayPool::cooldown(bool& abilityActive) {
    //how long ability lasts
    if (isFiring && abilityDuration >= 0.0f) {
        abilityDuration -= DeltaTime::getInstance()->getDeltaTime();
        if (abilityDuration <= 0.0f) {
            abilityCooldown = ABILITY_COOLDOWN;
            isFiring = false;
            shouldCast = false;
            alive = false;
            //
            abilityActive = false;
            return false; //not active--move
        }
        return true; //active--stop moving
    }
    //ability cooldown
    if (!shouldCast && abilityCooldown >= 0.0f) {
        abilityCooldown -= DeltaTime::getInstance()->getDeltaTime();
        if (abilityCooldown <= 0.0f) {
            abilityDuration = ABILITY_DURATION;
            shouldCast = true;
        }
    }
    return false; //on or not on cooldown--can move
}

void BulletSprayPool::activate(const sf::Vector2f& bossPos, GridSystem& grid) {
    if (fireCooldown.getElapsedTime().asSeconds() < FIRE_COOLDOWN) return;
    //
    isFiring = true; alive = true;
    auto bullet = std::move(shotsPool.back());
    shotsPool.pop_back();
    sf::Vector2f origin = calcStartPos(bossPos);
    bullet->setOriginPos(origin);
    bullet->activate(origin);
    grid.addEntity(*bullet);
    activeShots.push_back(std::move(bullet));
    fireCooldown.restart();
}

void BulletSprayPool::update(const sf::FloatRect& screenBounds, const sf::Vector2f& bossPos) {
    for (const auto& bullet : activeShots) {
        bullet->update(bossPos);
        bullet->isActive(screenBounds);
    }
}

void BulletSprayPool::cleanUp() {
    for (auto it = activeShots.begin(); it != activeShots.end(); ) {
        if (!(*it)->isAlive() || this->alive == false) {
            shotsPool.push_back(std::move(*it));
            it = activeShots.erase(it);
        } else {
            ++it;
        }
    }
}

sf::Vector2f BulletSprayPool::calcStartPos(const sf::Vector2f& bossPos) {
    const float zeroThreshold = 1e-6;
    sf::Vector2f position;
    if (curNumPos == maxNumPos) {
        curNumPos = 0;
        angleOffset += angleIncrement;
        if (angleOffset >= 2*M_PI) angleOffset -= 2*M_PI;
    }
    //
    float angle = 2*M_PI*curNumPos/maxNumPos + angleOffset;
    float x = std::cos(angle);
    float y = std::sin(angle);
    if (std::abs(x) < zeroThreshold) x = 0;
    if (std::abs(y) < zeroThreshold) y = 0;
    curNumPos++;
    //
    position.x = bossPos.x + radius*x;
    position.y = bossPos.y + radius*y;
    return position;
}

bool BulletSprayPool::canCast() const {
    return shouldCast;
}

void BulletSprayPool::render(sf::RenderWindow& window) const {
    for (const auto& bullet : activeShots) {
        bullet->render(window);
    }
}

//--------------------

const float BASE_DMG = 15.0f;
const float BASE_SLOW = 0.0f;

BulletSpray::BulletSpray() : 
    speed(500.0f), originPos({0.0f, 0.0f})
{
    collisionType = CIRCLE; entityType = ENEMY_ABILITY;
    debuff = {BASE_DMG, BASE_SLOW};
    //
    texture.loadFromFile("assets/enemies/bulletSpray.png");
    sprite.setTexture(texture);
    //
    bounds = {8, 7, 20, 24};
    hitBox.updateSize(bounds);
    sprite.setOrigin(sf::Vector2f((bounds.left + bounds.width/2.0f), (bounds.top + bounds.height/2.0f)));
    hitBox.followEntity(sprite.getPosition());
}

void BulletSpray::isActive(const sf::FloatRect& screenBounds) {
    debuff = {BASE_DMG, BASE_SLOW};

    sf::FloatRect expandedBounds = screenBounds;
    expandedBounds.left -= 500.0f; expandedBounds.top -= 500.0f;
    expandedBounds.width += 1000.0f; expandedBounds.height += 1000.0f;
    if (expandedBounds.contains(sprite.getPosition())) {
        alive = true;
    } else {
        alive = false;
    }
}

void BulletSpray::activate(const sf::Vector2f& spawnPos) {
    alive = true;
    sprite.setPosition(spawnPos);
    hitBox.followEntity(sprite.getPosition());
}

void BulletSpray::update(const sf::Vector2f& bossPos) {
    sf::Vector2f toBullet = sprite.getPosition() - bossPos;
    float angle = atan2(toBullet.y, toBullet.x); //relative to hor 
    //
    sf::Vector2f perpendicular;
    perpendicular.x = -sin(angle); //derivate of cos
    perpendicular.y = cos(angle);  //derivate of sin
    perpendicular = normalize(perpendicular);
    //
    sf::Vector2f outward = toBullet;
    outward = normalize(outward);
    //create spiral effect 
    float spiralFactor = 0.5; //controls tightness
    sf::Vector2f direction = perpendicular*(1 - spiralFactor) + outward*spiralFactor;
    //
    sf::Vector2f move = direction*speed*DeltaTime::getInstance()->getDeltaTime();
    sprite.move(move);
    hitBox.followEntity(sprite.getPosition());
    animateMovement();
}

void BulletSpray::animateMovement() {
    float rotationSpeed = 180.0f;
    float frameRotation = rotationSpeed * DeltaTime::getInstance()->getDeltaTime();
    sprite.rotate(frameRotation);
}

sf::Vector2f BulletSpray::attack() {
    float dist = std::abs(distance(sprite.getPosition(),  originPos));
    //stage 1 normal attack
    if (dist >= 650.0f) { //stage2: kinda far form boss
        debuff.x = debuff.x*1.5;
    } else if (dist >= 800.0f) { //stage3: really far from boss 
        debuff.x = debuff.x*2.3f;
        debuff.y = 0.75f;
    }
    return debuff;
}

void BulletSpray::setOriginPos(const sf::Vector2f& originPos) {
    this->originPos = originPos;
}

sf::FloatRect BulletSpray::getBounds() const {
    return hitBox.getBounds();
}

sf::Vector2f BulletSpray::getPosition() const {
    return sprite.getPosition();
}

void BulletSpray::handleCollision(Entity& entity) {
    EntityType otherEntity = entity.entityType;
    if (otherEntity == ENEMY || otherEntity == EXP || 
        otherEntity == TIMED_ABILITY || otherEntity == COLLISION_ABILITY || 
        otherEntity == ENEMY_ABILITY) return;
    //
    else if (otherEntity == PLAYER) {
        alive = false;
    } else if (otherEntity == OBSTACLE) {
        if (entity.isAlive()) {
            alive = false;
        }
    }
}

void BulletSpray::render(sf::RenderWindow& window) const {
    window.draw(sprite);
}