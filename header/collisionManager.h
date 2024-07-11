#pragma once
#include "utility.h"
#include "entity.h"
#include "collision.h"
#include "obstacles.h"

class CollisionManager {
private:
    std::vector<std::shared_ptr<Object>> objects;
    void handleEntityCollision(Entity& entity1, Entity& entity2);
    void handleObjectCollision(Entity& entity, Object& object);
public:
    std::vector<std::shared_ptr<Entity>> entities;
    //constructor
    CollisionManager() = default;
    ~CollisionManager() = default;
    //functions 
    void addEntity(std::shared_ptr<Entity> entity);
    void addObject(std::shared_ptr<Object> object);
    void checkCollisions();
};