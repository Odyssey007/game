#pragma once
#include "utility.h"
#include "entity.h"
#include "collision.h"
#include "obstacles.h"

class CollisionManager {
private:
    std::vector<std::shared_ptr<Entity>> entities;
    std::vector<std::shared_ptr<Object>> objects;
    void handleEntityCollision(Entity& entity1, Entity& entity2);
    void handleObjectCollision(Entity& entity, Object& object);
public:
    //constructor
    CollisionManager() = default;
    ~CollisionManager() = default;
    //functions 
    void addEntity(std::shared_ptr<Entity> entity);
    void addObject(std::shared_ptr<Object> object);
    void removeEntity(const std::shared_ptr<Entity>& entity);
    void removeObject(const std::shared_ptr<Object>& object);
    void update();
};