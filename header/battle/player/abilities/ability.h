#pragma once
#include "../header/utility.h"
#include "../header/animation.h"
#include "../header/battle/collision.h"
#include "../header/battle/entity.h"

enum PlayerAbilityType { BASICSLASH };

class Ability : public Entity {
protected:
    std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures;
    sf::Sprite sprite;
    //hitbox
    sf::FloatRect bounds;
    bool alive;
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
    Ability();
    virtual void activate(const sf::Vector2f& mousePosition, const sf::Vector2f& playerPosition) = 0;
    
    virtual bool isAlive() const override;
    virtual sf::FloatRect getBounds() const override;
    virtual sf::Vector2f getPosition() const override; 
    //setters
    virtual void setInitialPosition(const sf::FloatRect& screenBounds) override;
    //functions
    virtual void handleCollision(Entity& entity) override;
    // virtual void render(sf::RenderWindow& window) const override;
};