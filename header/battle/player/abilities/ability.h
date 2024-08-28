#pragma once
#include "../header/utility.h"
#include "../header/animation.h"
#include "../header/battle/collision.h"
#include "../header/battle/entity.h"

class Ability : public Entity {
protected:
    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> textures;
    sf::Sprite sprite;
    //animation
    sf::FloatRect bounds;
    Animation animation;
    sf::Vector2u animationSheetDim;
    float frameDuration;
    //!not implemented
    sf::Keyboard::Key key;
    sf::Mouse::Button mouseKey;
    //
    sf::Clock bufferTimer; //so it doesn't debuff multiple times on one attack
    void loadTexture(const std::string& name, const std::string& filePath);
public:
    bool stun; //!not implemented
    Ability();
    void restartBufferTime();
    float getBufferTime() const;
    virtual void kill();
    virtual sf::Vector2f hitEnemy();
    virtual void activate(const sf::Vector2f& mousePosition, const sf::Vector2f& playerPosition) = 0;
    // ENTITY
    virtual sf::Vector2f getPosition() const override; 
    //setters
    virtual void setInitialPosition(const sf::FloatRect& screenBounds) override;
    //functions
    virtual void handleCollision(Entity& entity) override;
    virtual void render(sf::RenderWindow& window) const override;
};