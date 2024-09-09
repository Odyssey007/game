#include "../header/battle/collisionManager.h"

//each entity locally evaluates what it should do after colliding with another entity
void CollisionManager::update(const std::vector<std::reference_wrapper<Entity>>& entities) {
    for (size_t i = 0; i < entities.size(); i++) {
        // entities-entities collisions
        for (size_t j = i + 1; j < entities.size(); j++) {
            Entity& entityA = entities[i].get(); 
            Entity& entityB = entities[j].get();
            helpPlayerGainNeighbor(entityA, entityB);
            if (isObstacleCheck(entityA, entityB)) {
                continue;
            } else {
                handleEntityCollision(entityA, entityB);
            }
        }
    }
}

//!diabolical--DON'T DELETE
#include "../header/battle/player/player.h"

void CollisionManager::helpPlayerGainNeighbor(Entity& entity1, Entity& entity2) {
    Player* player = nullptr;
    Entity* enemy = nullptr;
    if (entity1.entityType == PLAYER && entity2.entityType == ENEMY) {
        player = dynamic_cast<Player*>(&entity1);
        enemy = &entity2;
    } else if (entity2.entityType == PLAYER && entity1.entityType == ENEMY) {
        player = dynamic_cast<Player*>(&entity2);
        enemy = &entity1;
    }

    if (player) {
        player->findNearestEnemy(*enemy);
    }
}

bool CollisionManager::isObstacleCheck(Entity& entityA, Entity& entityB) {
    if ((entityA.entityType == OBSTACLE && (entityB.entityType == PLAYER || entityB.entityType == ENEMY)) ||
    (entityB.entityType == OBSTACLE && (entityA.entityType == PLAYER || entityA.entityType == ENEMY))) { 
        handleObjectCollision(entityA, entityB);
        return true;
    }
    return false;
}

//handle entities after colliding
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
        entity2.handleCollision(entity1);
    }
}

//handles entities before actually colliding
void CollisionManager::handleObjectCollision(Entity& entity1, Entity& entity2) {
    if (entity1.entityType == OBSTACLE) {
        if (!entity1.isAlive()) return;
        entity1.handleCollision(entity2);
    } else if (entity2.entityType == OBSTACLE) {
        if (!entity2.isAlive()) return;
        entity2.handleCollision(entity1);
    }
}