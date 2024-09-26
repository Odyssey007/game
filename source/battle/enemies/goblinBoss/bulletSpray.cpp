#include "../header/battle/enemies/goblinBoss/bulletSpray.h"

BulletSprayPool::BulletSprayPool() {
    numShots = 300;
    for (size_t i = 0; i < numShots; i++) {
        shotsPool.emplace_back(std::make_unique<BulletSpray>());
    }
}

const float FIRE_COOLDOWN = 0.1f;

void BulletSprayPool::activate(const sf::Vector2f& bossPos, GridSystem& grid) {
    if (fireCooldown.getElapsedTime().asSeconds() < FIRE_COOLDOWN) return;
    auto bullet = std::move(shotsPool.back());
    shotsPool.pop_back();
    bullet->activate(calcStartPos(bossPos));
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
        if (!(*it)->isAlive()) {
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
    if (curNumPos == maxNumPos) curNumPos = 0;
    //
    float angle = 2*M_PI*curNumPos/maxNumPos;
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

void BulletSprayPool::render(sf::RenderWindow& window) const {
    for (const auto& bullet : activeShots) {
        bullet->render(window);
    }
}

//--------------------

BulletSpray::BulletSpray() {
    collisionType = CIRCLE; entityType = ENEMY_ABILITY;
    //
    texture.loadFromFile("assets/enemies/bulletSpray.png");
    sprite.setTexture(texture);
    bounds = {8, 7, 20, 24};
    hitBox.updateSize(bounds);
    sprite.setOrigin(sf::Vector2f((bounds.left + bounds.width/2.0f), (bounds.top + bounds.height/2.0f)));

    sprite.setPosition(500, 600);
    hitBox.followEntity(sprite.getPosition());
}

void BulletSpray::isActive(const sf::FloatRect& screenBounds) {
    if (screenBounds.contains(sprite.getPosition())) {
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
    float deltaTime = DeltaTime::getInstance()->getDeltaTime();

    // Update the angle to rotate
    angle += angleIncrement * deltaTime;
    if (angle > M_PI) {
        angle = 0;
    }

    float sign = 1;
    if (bossPos.x >= sprite.getPosition().x) { //left
        sign = -1; 
    }

    // Increase the radius (distance from the origin) over time
    radius += expansionSpeed * deltaTime;

    // Calculate the new position based on the current angle and radius
    sf::Vector2f myPos = normalize(sprite.getPosition());

    sf::Vector2f newPos(
        myPos.x + radius * std::cos(angle),
        myPos.y + radius * std::sin(angle)
    );


    newPos = normalize(newPos);
    newPos *= sign*350;

    // Set the sprite's new position
    sprite.move(newPos);
}



void BulletSpray::animateMovement() {
    float rotationSpeed = 180.0f;
    float frameRotation = rotationSpeed * DeltaTime::getInstance()->getDeltaTime();
    
    sprite.rotate(frameRotation);
}

sf::FloatRect BulletSpray::getBounds() const {
    return hitBox.getBounds();
}

sf::Vector2f BulletSpray::getPosition() const {
    return sprite.getPosition();
}

void BulletSpray::render(sf::RenderWindow& window) const {
    window.draw(sprite);
    window.draw(hitBox.body);
}