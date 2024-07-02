#pragma once
#include "utility.h"
#include "entity.h"
#include "collision.h"

class CollisionManager {
private:
    std::vector<std::shared_ptr<Entity>> entities;
    void handleCollision(Entity& entity1, Entity& entity2);
public:
    //constructor
    CollisionManager();
    ~CollisionManager();
    //functions 
    void addEntity(std::shared_ptr<Entity> entity);
    void checkCollisions();
};