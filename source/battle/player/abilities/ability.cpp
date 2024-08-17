#include "../header/battle/player/abilities/ability.h"

Abilities::Abilities() :
    animationSheetDim(sf::Vector2f(0.0f, 0.0f)), frameDuration(0.0f)
{
    loadTexture("basicSlash", "assets/slashSheet.png");
    
}

void Abilities::loadTexture(const std::string& name, const std::string& filePath) {
    sf::Texture texture;
    if (texture.loadFromFile(filePath)) {
        textures[name] = texture;
    } else {
        throw std::runtime_error ("Failed to load enemy texture");
    }
}