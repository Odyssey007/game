#pragma once
#include "../header/utility.h"
#include "../header/battle/entity.h"
#include "../header/battle/collision.h"

class CollisionManager {
private:

    void handleEntityCollision(Entity& entity1, Entity& entity2);
    void handleObjectCollision(Entity& entity1, Entity& entity2);
public:
    //constructor
    CollisionManager() = default;
    ~CollisionManager() = default;
    //functions 
    void update(const std::vector<std::reference_wrapper<Entity>>& entities);
};