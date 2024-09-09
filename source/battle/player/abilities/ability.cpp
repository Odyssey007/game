#include "../header/battle/player/abilities/ability.h"

Ability::Ability() :
    animationSheetDim(sf::Vector2f(0.0f, 0.0f)), frameDuration(0.0f)
{
    loadTexture("basicSlash", "assets/abilities/slashSheet.png");
    loadTexture("blast", "assets/abilities/blastSheet.png");
}

void Ability::loadTexture(const std::string& name, const std::string& filePath) {
    auto texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile(filePath)) {
        throw std::runtime_error("Failed to load enemy texture: " + filePath);
    }
    textures.emplace(name, std::move(texture));
}

void Ability::activate(const sf::Vector2f& mousePosition, const sf::Vector2f& playerPosition) {
    return;
}

void Ability::activate(const sf::Vector2f& mousePosition, sf::Vector2f& playerPosition) {
    return;
}

void Ability::restartBufferTime() {
    bufferTimer.restart();
}

float Ability::getBufferTime() const {
    return bufferTimer.getElapsedTime().asSeconds();
}

void Ability::kill() {
    alive = false;
};

//base debuff by all ability
sf::Vector2u Ability::hitEnemy() {
    return sf::Vector2u(10, 0);
}

// ENTITY

sf::Vector2f Ability::getPosition() const {
    return sprite.getPosition();
}

void Ability::setInitialPosition(const sf::FloatRect& screenBounds) {
    return;
}

void Ability::handleCollision(Entity& entity) {
    EntityType otherEntity = entity.entityType;
    if (otherEntity == PLAYER || otherEntity == EXP ||
        otherEntity == BLAST) return;
    if (otherEntity == ENEMY) {
        kill();
    } else if (otherEntity == OBSTACLE) {
        if (entity.isAlive()) {
            kill();
        }
    }
}

void Ability::render(sf::RenderWindow& window) const {
    window.draw(sprite);
}