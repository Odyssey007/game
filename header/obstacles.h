#pragma once
#include "utility.h"
#include "entity.h"
#include "collision.h"

//obstacleType: 0 - non-dmg | 1 - dmg

class StaticObstacle : public Entity {
private:
    //texture
    sf::RectangleShape obstacle; //?temporary
    sf::Texture texture;
    sf::Sprite sprite;
    //hitbox
    BoxCollision hitBox;
    sf::IntRect bounds;
    //functions
    void handleCollisionBox(Entity& entity);
    void handleCollisionCircle(Entity& other);
public:
    StaticObstacle();
    //functions
    virtual void initialPosition() override;
    virtual void handleCollisions(Entity& other) override;
    virtual void render(sf::RenderWindow& window) override;
    //fetchers
    virtual size_t getState() override;
    virtual sf::Shape& getShape() override;
};






class DynamicObstacle : public Entity {
private:
    //texture
    sf::Texture texture;
    sf::Sprite sprite;

public:
    DynamicObstacle();
    //functions
    virtual void initialPosition() override;
    virtual void handleCollisions(Entity& other) override;
    virtual void render(sf::RenderWindow& window) override;
    //fetchers
    virtual size_t getState() override;
    virtual sf::Shape& getShape() override;
};