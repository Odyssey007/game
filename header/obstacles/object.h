#pragma once
#include "../header/utility.h"
#include "../header/entity.h"
#include "../header/collision.h"
#include "../header/entity.h"



class Object : public Entity {
private:
    //texture
    std::vector<std::shared_ptr<sf::Texture>> textures;
    sf::Sprite sprite;
    //hitbox
    sf::FloatRect bounds;
    //functions
    sf::FloatRect currentBounds;
    void resolveBoxCollision(sf::Vector2f& velocity, const sf::FloatRect& entityBounds);
    void resolveCircleCollision(sf::Vector2f& velocity, const sf::FloatRect& entityBounds);
public:
    // sf::RectangleShape obstacle; //?temporary
    void loadTexture(const std::string& filePath);

    Object();
    //functions

    //sf::FloatRect getGlobalBounds();
    //
    virtual bool isAlive() const override; //?idk
    virtual sf::FloatRect getBounds() const override;
    virtual sf::Vector2f getPosition() const override;
    //
    virtual void setInitialPosition(const sf::FloatRect& screenBounds) override;
    //
    virtual void handleCollision(Entity& entity) override;
    virtual void render(sf::RenderWindow& window) const override;
};