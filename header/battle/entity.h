#pragma once 
#include "../header/utility.h"

//COLLISION_ABILITY: dies after hitting
//TIMED_ABILITY: doesn't die after hitting
enum EntityType { 
    PLAYER, ENEMY, OBSTACLE, EXP, 
    COLLISION_ABILITY, TIMED_ABILITY 
};
enum CollisionType { BOX, CIRCLE };

class Entity {
protected:
    bool alive;
public:
    Entity();
    EntityType entityType;
    CollisionType collisionType;
    //fetchers
    virtual bool isAlive() const;
    virtual sf::FloatRect getBounds() const = 0; //gets globalBounds()
    virtual sf::Vector2f getPosition() const = 0;
    virtual const sf::Vector2f& getVelocity() const;
    //setters
    virtual void setVelocity(const sf::Vector2f& velocity);
    virtual void setInitialPosition(const sf::FloatRect& screenBounds) = 0;
    //functions
    virtual void applyMovement(); 
    virtual void handleCollision(Entity& entity) = 0;
    virtual void render(sf::RenderWindow& window) const = 0;
};