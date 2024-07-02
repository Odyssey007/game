#pragma once 
#include "utility.h"

enum EntityType { PLAYER, ENEMY, OBSTACLE };
enum EnemyType { SLIME };
enum CollisionType { AABB, CIRCLE };

class Entity {
protected:
public:
    EnemyType enemyType;
    EntityType entityType;
    CollisionType collisionType;
    //functions
    virtual void initialPosition() = 0;
    virtual void handleCollisions(Entity& other) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    //fetches
    virtual size_t getState() = 0;
    virtual sf::Shape& getShape() = 0;
};