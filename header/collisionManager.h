#pragma once
#include "../header/utility.h"
#include "../header/entity.h"
#include "../header/collision.h"
#include "../header/obstacles/object.h"

class CollisionManager {
private:

    void handleEntityCollision(Entity& entity1, Entity& entity2);
    void handleObjectCollision(Entity& entity1, Entity& entity2);
public:
    //constructor
    CollisionManager() = default;
    ~CollisionManager() = default;
    //functions 
    void update(const std::vector<std::shared_ptr<Entity>> entities);
};