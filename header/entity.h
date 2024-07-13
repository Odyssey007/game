#pragma once 
#include "../header/utility.h"

enum EntityType { PLAYER, ENEMY, OBSTACLE };
enum EnemyType { SLIME };
enum CollisionType { AABB, CIRCLE };

class Entity {
protected:
public:
    Entity() = default;
    ~Entity() = default;
    EntityType entityType;
    CollisionType collisionType;
    EnemyType enemyType;
    //fetchers
    virtual bool isAlive() const = 0;
    virtual int getState() const = 0; //gets enemy move -- as of now
    virtual sf::FloatRect getBounds() const = 0; //gets the globalBounds()
    virtual sf::Vector2f getPosition() const = 0; //gets position
    virtual const sf::Vector2f& getVelocity() const = 0; //gets entity movement speed
    //setters
    virtual void setVelocity(const sf::Vector2f& velocity) = 0; //changes entity movement speed
    virtual void setInitialPosition(const sf::Vector2u& position) = 0; //sets inital position of entities
    //functions
    virtual void applyMovement() = 0;
    virtual void handleCollision(Entity& entity) = 0;
    virtual void render(sf::RenderWindow& window) const = 0;
};