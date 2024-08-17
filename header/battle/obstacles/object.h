#pragma once
#include "../header/utility.h"
#include "../header/battle/entity.h"
#include "../header/battle/collision.h"
#include "../header/battle/entity.h"

//obstacleType: 0 - non-dmg | 1 - dmg

class Object : public Entity {
private:
    //texture
    sf::Texture texture;
    sf::Sprite sprite;
    //hitbox
    BoxCollision hitBox;
    sf::FloatRect bounds;
    sf::FloatRect currentBounds;
    //functions
    void resolveBoxCollision(sf::Vector2f& velocity, const sf::FloatRect& entityBounds);
    void resolveCircleCollision(sf::Vector2f& velocity, const sf::FloatRect& entityBounds);
public:
    sf::RectangleShape obstacle; //?temporary

    Object();
    //functions

    //sf::FloatRect getGlobalBounds();
    //
    virtual bool isAlive() const override; //?idk
    virtual int getState() const override; //?might need
    virtual sf::FloatRect getBounds() const override;
    virtual sf::Vector2f getPosition() const override;
    virtual const sf::Vector2f& getVelocity() const override; //!nope
    //
    virtual void setVelocity(const sf::Vector2f& velocity) override; //!nope
    virtual void setInitialPosition(const sf::View& view) override;
    //
    virtual void applyMovement() override; //!nope
    virtual void handleCollision(Entity& entity) override;
    virtual void render(sf::RenderWindow& window) const override;
};