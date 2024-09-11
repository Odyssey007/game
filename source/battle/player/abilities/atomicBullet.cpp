#include "../header/battle/player/abilities/atomicBullet.h"

AtomicBulletPool::AtomicBulletPool(size_t totalBullets) {
    totalAmmo = totalBullets;
    for (size_t i = 0; i < totalAmmo; ++i) {
        allBullets.emplace_back(std::make_unique<AtomicBullet>());
        allResidue.emplace_back(std::make_unique<AtomicResidue>()); //?change maybe
    }
}

bool AtomicBulletPool::spawnProjectile(const sf::Vector2f& target, const sf::Vector2f& playerPos, GridSystem& grid) {
    if (magnitude(target) == 0) return false; //!enemy null
    if (fireCooldown.getElapsedTime().asSeconds() >= 3.15f) {
        auto bullet = std::move(allBullets.back());
        allBullets.pop_back();
        bullet->startPosition(playerPos, target);
        bullet->activate(target, playerPos);
        grid.addEntity(*bullet);
        activeBullets.push_back(std::move(bullet));
        fireCooldown.restart();
        return true;
    }
    return false;
}

void AtomicBulletPool::update(const sf::FloatRect screenBounds) {
    for (const auto& bullet : activeBullets) {
        bullet->isActive(screenBounds);
    }
    //residue
    for (auto& residue : activeResidue) {
        residue->isActive();
        residue->update();
    }
}

void AtomicBulletPool::cleanUp(GridSystem& grid) {
    for (auto it = activeBullets.begin(); it != activeBullets.end(); ) {
        if (!(*it)->isAlive()) {
            //checks if just left the screen
            if (!(*it)->isGoneOut()) {
                spawnResidue((*it)->getPosition(), grid);
            }
            allBullets.push_back(std::move(*it));
            it = activeBullets.erase(it);
        } else {
            (*it)->update();
            ++it;
        }
    }
    //residue
    for (auto it = activeResidue.begin(); it != activeResidue.end(); ) {
        if (!(*it)->isAlive()) {
            allResidue.push_back(std::move(*it));
            it = activeResidue.erase(it);
        } else {
            ++it;
        }
    }
}

void AtomicBulletPool::spawnResidue(const sf::Vector2f& bulletPos, GridSystem& grid) {
    if (!allResidue.empty()) {
        auto residue = std::move(allResidue.back());
        allResidue.pop_back();
        residue->startPosition(bulletPos);
        grid.addEntity(*residue);
        activeResidue.push_back(std::move(residue));
    }
}

void AtomicBulletPool::render(sf::RenderWindow& window) const {
    for (const auto& bullet : activeBullets) {
        bullet->render(window);
    }

    for (const auto& residue : activeResidue) {
        residue->render(window);
    }
}

//------------------ ATOMIC RESIDUE

AtomicResidue::AtomicResidue() {
    setProperties();
    //!implement slow later
    debuff = sf::Vector2u(10, 100);
    //
    collisionType = CIRCLE; entityType = TIMED_ABILITY; stun = false;
    animationSheetDim = sf::Vector2u(4, 1); frameDuration = 0.2f;
    sprite.setTexture(*textures["atomicResidue"]);
    animation = Animation(*textures["atomicResidue"], animationSheetDim, frameDuration);
    sprite.setTextureRect(animation.uvRect);
    //hitbox
    bounds = sf::FloatRect(1.8f, 2.f, 20.5f, 20.5f);
    hitBox.updateSize(bounds);
    //inital scale
    sprite.setScale(curScale, curScale);
    sprite.setOrigin(sf::Vector2f((bounds.left + bounds.width/2.0f), (bounds.top + bounds.height/2.0f)));
    //scale
    targetScale = 5.0f; 
    scaleDuration = .75f;
}

void AtomicResidue::setProperties() {
    //scale
    curScale = 1.0f;
    elapsedTime = 0.0f;
    upScale = true; downScale = false;
    //
    upTime = 5.0f;
    alive = true;
}

void AtomicResidue::startPosition(const sf::Vector2f& bulletPos) {
    sprite.setPosition(bulletPos);
    hitBox.followEntity(sprite.getPosition());
    setProperties();
}

void AtomicResidue::isActive() {
    upTime -= DeltaTime::getInstance()->getDeltaTime();
    if (upTime <= 0.0f) {
        alive = false;
    } else if (upTime <= .75 && !downScale) {
        downScale = true;
        elapsedTime = 0.0f;
    }
}

sf::FloatRect AtomicResidue::calcBounds(float scale) {
    sf::FloatRect originalBounds = sprite.getLocalBounds();
    float hitboxScaleFactor = 0.85;
    //scale down
    float adjustedWidth = originalBounds.width * scale * hitboxScaleFactor;
    float adjustedHeight = originalBounds.height * scale * hitboxScaleFactor;
    //center on sprite position
    sf::Vector2f spriteCenter = sprite.getPosition();
    float left = spriteCenter.x - adjustedWidth / 2;
    float top = spriteCenter.y - adjustedHeight / 2;
    //
    return sf::FloatRect(left, top, adjustedWidth, adjustedHeight);
}

void AtomicResidue::enlargeSize() {
    if (elapsedTime <= scaleDuration) {
        elapsedTime += DeltaTime::getInstance()->getDeltaTime();
        curScale = 1.0f + (targetScale - 1.0f)*(elapsedTime/scaleDuration);
        sprite.setScale(curScale, curScale);
    } else {
        sprite.setScale(targetScale, targetScale);
        curScale = targetScale;
        upScale = false;
    }
    hitBox.updateSize(calcBounds(curScale));
}

void AtomicResidue::reduceSize() {
    if (elapsedTime <= scaleDuration) {
        elapsedTime += DeltaTime::getInstance()->getDeltaTime();
        curScale = targetScale - (targetScale - 1.0f)*(elapsedTime/scaleDuration);
        sprite.setScale(curScale, curScale);
    } else {
        curScale = 1.0f;
        sprite.setScale(curScale, curScale);
        downScale = false;
    }
    hitBox.updateSize(calcBounds(curScale));
}

void AtomicResidue::update() {
    if (upScale) enlargeSize();
    if (downScale) reduceSize();
    //
    animation.update(sprite, 0, true, {curScale, curScale});
}

sf::Vector2u AtomicResidue::hitEnemy() {
    return debuff;
}

sf::FloatRect AtomicResidue::getBounds() const {
    return hitBox.getBounds();
}

//------------------ ATOMIC BULLET

AtomicBullet::AtomicBullet() {
    move = sf::Vector2f(0.0f, 0.0f);
    speed = 200.0f; debuff = sf::Vector2u(0, 0); diedGoingOut = false;

    collisionType = CIRCLE; entityType = COLLISION_ABILITY; stun = false;
    sprite.setTexture(*textures["atomicBullet"]);
    //hitbox
    bounds = sf::FloatRect(0.0f, 0.0f, 18.5f, 18.5f);
    hitBox.updateSize(bounds);
    //
    sprite.setScale(1.7f, 1.7f);
    sprite.setOrigin(sf::Vector2f((bounds.left + bounds.width/2.0f), (bounds.top + bounds.height/2.0f)));
}

void AtomicBullet::startPosition(const sf::Vector2f& playerPosition, const sf::Vector2f& mousePosition) {
    if (mousePosition.x >= playerPosition.x) { //right
        sprite.setPosition(playerPosition.x + sprite.getGlobalBounds().width/2.0f + 8.0f, playerPosition.y - 3.0f);
    } else { //left
        sprite.setPosition(playerPosition.x - sprite.getGlobalBounds().width/2.0f - 8.0f, playerPosition.y - 3.0f);
    }
    hitBox.followEntity(sprite.getPosition());
}

//gets direction
void AtomicBullet::activate(const sf::Vector2f& mousePosition, const sf::Vector2f& playerPosition) {    
    move = sf::Vector2f(0.0f, 0.0f);
    sf::Vector2f direction = normalize(mousePosition - playerPosition);
    move = direction*speed;
}

void AtomicBullet::update() {
    sf::Vector2f frameMove = move*DeltaTime::getInstance()->getDeltaTime();
    sprite.move(frameMove);
    hitBox.followEntity(sprite.getPosition());
    //animation
    float rotationSpeed = 90.0f;
    float frameRotation = rotationSpeed*DeltaTime::getInstance()->getDeltaTime();
    sprite.rotate(frameRotation);
}

void AtomicBullet::isActive(const sf::FloatRect screenBounds) {
    sf::Vector2f currentPosition = sprite.getPosition();
    
    if (screenBounds.contains(currentPosition)) {
        alive = true;
        diedGoingOut = false;
    } else {
        alive = false;
        diedGoingOut = true;
    }
}

bool AtomicBullet::isGoneOut() const {
    return diedGoingOut;
}

sf::FloatRect AtomicBullet::getBounds() const {
    return hitBox.getBounds();
}

sf::Vector2u AtomicBullet::hitEnemy() {
    return debuff;
}