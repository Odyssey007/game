#pragma once
#include "../header/utility.h"
#include "../header/animation.h"
#include "../header/collision.h"
#include "../header/entity.h"

enum PlayerAbilityType { BASICSLASH };

class Ability : public Entity {
protected:
    std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures;
    sf::Sprite sprite;
    sf::FloatRect bounds;
    //animation
    Animation animation;
    sf::Vector2u animationSheetDim;
    float frameDuration;
    //key
    sf::Keyboard::Key key;
    sf::Mouse::Button mouseKey;
    //
    PlayerAbilityType abilityType; //not initalized

    bool alive;

    void loadTexture(const std::string& name, const std::string& filePath);
public:
    bool active; //!need to implement
    Ability();
    virtual void activate(const sf::Vector2f& mousePosition, const sf::Vector2f& playerPosition) = 0;
    //entity
    virtual bool isAlive() const override;
    virtual sf::FloatRect getBounds() const override; //!not here
    virtual sf::Vector2f getPosition() const override; //!not here
    
    virtual void setInitialPosition(const sf::FloatRect& screenBounds); //!not needed maybe
    
    virtual void handleCollision(Entity& entity) override; //!not here
    // virtual void render(sf::RenderWindow& window) const override;
};