#include "../header/battle/player/abilities/blast.h"

BlastPool::BlastPool(size_t totalBlasts) {
    totalAmmo = totalBlasts;
    for (size_t i = 0; i < totalAmmo; ++i) {
        allBlasts.emplace_back(std::make_unique<Blast>());
    }
}

bool BlastPool::spawnProjectile(const sf::Vector2f& mousePos, const sf::Vector2f& playerPos, GridSystem& grid) {
    if (fireCooldown.getElapsedTime().asSeconds() >= 0.15f) {
        auto blast = std::move(allBlasts.back());
        allBlasts.pop_back();
        blast->startPosition(playerPos, mousePos);
        blast->activate(mousePos, playerPos);
        grid.addEntity(*blast);
        activeBlasts.push_back(std::move(blast));
        fireCooldown.restart();
        return true;
    }
    return false;
}

void BlastPool::update(const sf::FloatRect screenBounds) {
    for (const auto& blast : activeBlasts) {
        blast->isActive(screenBounds);
    }
}

void BlastPool::cleanUp() {
    for (auto it = activeBlasts.begin(); it != activeBlasts.end(); ) {
        if (!(*it)->isAlive()) {
            allBlasts.push_back(std::move(*it));
            it = activeBlasts.erase(it);
        } else {
            (*it)->update();
            ++it;
        }
    }
}

void BlastPool::render(sf::RenderWindow& window) const {
    for (const auto& blast : activeBlasts) {
        blast->render(window);
    }
}

//------------------

Blast::Blast() : 
    move(0.0f, 0.0f),
    blastSpeed(800.0f), debuff(100, 0)
{
    //preliminaries
    collisionType = CIRCLE; entityType = COLLISION_ABILITY; stun = false;
    animationSheetDim = sf::Vector2u(4, 1); frameDuration = 0.15f; 
    sprite.setTexture(*textures["blast"]);
    animation = Animation(*textures["blast"], animationSheetDim, frameDuration);
    sprite.setTextureRect(animation.uvRect);
    //hitbox
    bounds = sf::FloatRect(140, 140, 22, 22);
    hitBox.updateSize(bounds);
    //
    sprite.setOrigin(sf::Vector2f((bounds.left + bounds.width/2.0f), (bounds.top + bounds.height/2.0f)));
    sprite.setScale(0.1f, 0.1f);
}

//where to spawn
void Blast::startPosition(const sf::Vector2f& playerPosition, const sf::Vector2f& mousePosition) {
    if (mousePosition.x >= playerPosition.x) { //right
        sprite.setPosition(playerPosition.x + sprite.getGlobalBounds().width/2.0f + 8.0f, playerPosition.y - 3.0f);
    } else { //left
        sprite.setPosition(playerPosition.x - sprite.getGlobalBounds().width/2.0f - 8.0f, playerPosition.y - 3.0f);
    }
    hitBox.followEntity(sprite.getPosition());
}

//gets direction
void Blast::activate(const sf::Vector2f& mousePosition, const sf::Vector2f& playerPosition) {    
    move = sf::Vector2f(0.0f, 0.0f);
    sf::Vector2f direction = normalize(mousePosition - playerPosition);
    move = direction*blastSpeed;
}

//moves/animates it
void Blast::update() {
    sf::Vector2f frameMove = move*DeltaTime::getInstance()->getDeltaTime();
    sprite.move(frameMove);
    hitBox.followEntity(sprite.getPosition());
    animation.update(sprite, 0, true, {0.1f, 0.1f});
}

//checks if within screen
void Blast::isActive(const sf::FloatRect screenBounds) {
    sf::Vector2f currentPosition = sprite.getPosition();
    alive = screenBounds.contains(currentPosition);
}

//returns dmg blast will deal
sf::Vector2u Blast::hitEnemy() {
    return debuff;
}

sf::FloatRect Blast::getBounds() const {
    return hitBox.getBounds();
}