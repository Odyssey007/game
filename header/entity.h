#pragma once 
#include "utility.h"

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
    virtual size_t getState() = 0; //gets enemy move -- as of now
    virtual const sf::Shape& getShape() = 0; //gets hitbox body
    virtual const sf::Vector2f& getVelocity() = 0; //gets entity movement speed
    //setters
    virtual void setVelocity(const sf::Vector2f& velocity) = 0; //changes entity movement speed
    virtual void setInitialPosition(const sf::Vector2u& position) = 0; //sets inital position of entities
    //functions
    virtual void handleCollision(Entity& entity) = 0; 
    virtual void render(sf::RenderWindow& window) = 0;


    virtual void applyMovement() = 0;
};