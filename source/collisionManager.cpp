#include "../header/collisionManager.h"

//clears when starting
CollisionManager::CollisionManager() {
    entities.clear();
}

//clears when ending :D
CollisionManager::~CollisionManager() {
    entities.clear();
}

//adds entity into the lil vector
void CollisionManager::addEntity(std::shared_ptr<Entity> entity) {
    entities.push_back(std::move(entity));
}

//!currently->brute forces through all entities spawned for collision check 
void CollisionManager::checkCollisions() {
    bool hit = false;

    for (size_t i = 0; i < entities.size(); i++) {
        for (size_t j = i+1; j < entities.size(); j++) {
            if (entities[i]->collisionType == entities[j]->collisionType) {
                if (entities[i]->collisionType == AABB) {
                    hit = BoxCollision::checkCollision(entities[i]->getShape(), entities[j]->getShape());
                } else if (entities[i]->collisionType == CIRCLE) {
                    hit = CircleCollision::checkCollision(entities[i]->getShape(), entities[j]->getShape());
                }
            } else if (entities[i]->collisionType != entities[j]->collisionType) {
                if (entities[i]->collisionType == AABB && entities[j]->collisionType == CIRCLE) {
                    hit = Collision::checkCollision(entities[i]->getShape(), entities[j]->getShape());
                }
            }
            if (hit) {
                handleCollision(*entities[i], *entities[j]);
            }
        }
    }

}

//handles what to do once entity1 collides with entity2
void CollisionManager::handleCollision(Entity& entity1, Entity& entity2) {
    entity1.handleCollisions(entity2);
}