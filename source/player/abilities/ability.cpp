#include "../header/player/abilities/ability.h"

Ability::Ability() :
    animationSheetDim(sf::Vector2f(0.0f, 0.0f)), frameDuration(0.0f)
{
    loadTexture("basicSlash", "assets/abilities/slashSheet.png");
    loadTexture("blast", "assets/abilities/blastSheet.png");
}

void Ability::loadTexture(const std::string& name, const std::string& filePath) {
    auto texture = std::make_shared<sf::Texture>(); 
    if (texture->loadFromFile(filePath)) {
        textures[name] = texture;
    } else {
        throw std::runtime_error("Failed to load enemy texture");
    }
}

bool Ability::isAlive() const {
    return alive;
}

// void Ability::render(sf::RenderWindow& window) const {
//     window.draw(sprite);
// }

sf::FloatRect Ability::getBounds() const {
    return bounds;
}

sf::Vector2f Ability::getPosition() const {
    return sprite.getPosition();
}

void Ability::setInitialPosition(const sf::FloatRect& screenBounds) {
    return;
}

void Ability::handleCollision(Entity& entity) {
    return;
}