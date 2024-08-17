#include "../header/battle/collisionManager.h"

//!currently.brute forces through all entities spawned for collision check 
void CollisionManager::update(const std::vector<std::shared_ptr<Entity>>& entities) {
    for (size_t i = 0; i < entities.size(); i++) {
        //entities-entities collisions
        for (size_t j = i+1; j < entities.size(); j++) {
            if (entities[j]->entityType == OBSTACLE) {
                handleObjectCollision(*entities[i], *entities[j]);
            } else {
                handleEntityCollision(*entities[i], *entities[j]); 
            }
        }
    }
}

void CollisionManager::handleEntityCollision(Entity& entity1, Entity& entity2) {
    bool collided = false;

    if (entity1.collisionType == entity2.collisionType) {
        if (entity1.collisionType == BOX) { // both are box collision
            collided = BoxCollision::checkCollision(entity1.getBounds(), entity2.getBounds());
        } else if (entity1.collisionType == CIRCLE) { // both are circle collision
            collided = CircleCollision::checkCollision(entity1.getBounds(), entity2.getBounds());
        } 
    } else { // box-circle collision
        collided = Collision::checkCollision(entity1.getBounds(), entity2.getBounds());
    }
    if (collided) {
        entity1.handleCollision(entity2);
    }
}

void CollisionManager::checkCollisionType(Entity& entity1, Entity& entity2) {
    bool collided = false;

    if (entity1.collisionType == entity2.collisionType) {
        if (entity1.collisionType == BOX) { //box-box
            collided = BoxCollision::checkCollision(entity1.getBounds(), entity2.getBounds());
            if (entity1.entityType == ENEMY && entity2.entityType == ENEMY) {

            }
        } else if (entity1.collisionType == CIRCLE) { //circle-circle
            collided = CircleCollision::checkCollision(entity1.getBounds(), entity2.getBounds());
        } 
    } else { //box-circle
        collided = Collision::checkCollision(entity1.getBounds(), entity2.getBounds());
    }
    if (collided) {
        entity1.handleCollision(entity2);
    }
}

void CollisionManager::handleObjectCollision(Entity& entity1, Entity& entity2) {
    if (entity1.entityType == OBSTACLE) {
        entity1.handleCollision(entity2);
    }
    entity2.handleCollision(entity1);
}