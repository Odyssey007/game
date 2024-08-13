#include "../header/collisionManager.h"

//adds entity into the lil vector
// void CollisionManager::addEntity(std::shared_ptr<Entity> entity) {
//     entities.push_back(std::move(entity));
// }

// void CollisionManager::addObject(std::shared_ptr<Object> object) {
//     objects.push_back(std::move(object));
// }

// void CollisionManager::removeEntity(const std::shared_ptr<Entity>& entity) {
//     entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
// }

// void CollisionManager::removeObject(const std::shared_ptr<Object>& object) {
//     objects.erase(std::remove(objects.begin(), objects.end(), object), objects.end());
// }

//!currently.brute forces through all entities spawned for collision check 
void CollisionManager::update(const std::vector<std::shared_ptr<Entity>> entities) {
    for (size_t i = 0; i < entities.size(); i++) {
        //entities-objects collisions
        // for (size_t j = 0; j < objects.size(); j++) {
        //     
        // }
        //entities-entities collisions
        for (size_t j = i+1; j < entities.size(); j++) {
            if (entities[j]->entityType == 2) {
                handleObjectCollision(*entities[i], *entities[j]);
            } else {
                handleEntityCollision(*entities[i], *entities[j]); 
            }
        }
    }
}

void CollisionManager::handleEntityCollision(Entity& entity1, Entity& entity2) {
    bool collided = false;

    //handles enemy not being able to phase through one another
    if (entity1.entityType == ENEMY && entity2.entityType == ENEMY) {
        entity1.handleCollision(entity2);
    } else {
        if (entity1.collisionType == entity2.collisionType) {
            if (entity1.collisionType == AABB) { //both are box collision
                collided = BoxCollision::checkCollision(entity1.getBounds(), entity2.getBounds());
            } else if (entity1.collisionType == CIRCLE) { //both are circle collision
                collided = CircleCollision::checkCollision(entity1.getBounds(), entity2.getBounds());
            } 
        } else { //box-circle collision
                collided = Collision::checkCollision(entity1.getBounds(), entity2.getBounds());
            }
        if (collided) {
            entity1.handleCollision(entity2);
        }
    }
}

void CollisionManager::handleObjectCollision(Entity& entity1, Entity& entity2) {
    if (entity1.entityType == 2) {
        entity1.handleCollision(entity2);
    }
    entity2.handleCollision(entity1);
}