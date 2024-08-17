#pragma once
#include "../header/battle/utility.h"
#include "../header/battle/animation.h"
#include "../header/battle/collision.h"

enum PlayerAbilityType { BASICSLASH };

class Abilities {
protected:
    std::unordered_map<std::string, sf::Texture> textures;
    sf::Sprite sprite;
    //animation
    Animation animation;
    sf::Vector2u animationSheetDim;
    float frameDuration;
    //key
    sf::Keyboard::Key key;
    sf::Mouse::Button mouseKey;
    //
    PlayerAbilityType abilityType; //not initalized

    void loadTexture(const std::string& name, const std::string& filePath);
public:
    bool active; //!need to implement
    Abilities();
    virtual void activate(const sf::Vector2f& mousePosition, const sf::Vector2f& playerPosition) = 0;
    virtual void render(sf::RenderWindow& window) const = 0;
};