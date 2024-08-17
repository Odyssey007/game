#pragma once 
#include "../header/utility.h"

enum EntityType { PLAYER, ENEMY, OBSTACLE };
enum EnemyType { SLIME, GOBLIN };
enum CollisionType { BOX, CIRCLE };

class Entity {
protected:
public:
    Entity() = default;
    virtual ~Entity() = default;
    EntityType entityType;
    CollisionType collisionType;
    EnemyType enemyType;
    //fetchers
    virtual bool isAlive() const = 0;
    virtual sf::FloatRect getBounds() const = 0; //gets the globalBounds()
    virtual sf::Vector2f getPosition() const = 0; //gets position
    virtual const sf::Vector2f& getVelocity() const;  //gets movement speed
    //setters
    virtual void setVelocity(const sf::Vector2f& velocity); //changes movement speed
    virtual void setInitialPosition(const sf::FloatRect& screenBounds) = 0; //sets inital position 
    //functions
    virtual void applyMovement(); 
    virtual void handleCollision(Entity& entity) = 0;
    virtual void render(sf::RenderWindow& window) const = 0;
};