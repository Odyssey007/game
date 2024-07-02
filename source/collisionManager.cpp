#include "header/collisionManager.h"
#include "header/game.h"

//!muy bad copying these over 
template <>
void CollisionManager::addEntity<RecCollision>(RecCollision entity) {
    entityRecHitBox.push_back(entity);
}

template <>
void CollisionManager::addEntity<CircleCollision>(CircleCollision entity) {
    entityCirHitBox.push_back(entity);
}

void CollisionManager::checkCollisions () {
    bool hit = false;

    for (size_t i = 0; i <= entityRecHitBox.size(); i++) {
        for (size_t j = 0; j <= entityRecHitBox.size(); j++) {
            hit = entityRecHitBox[i].checkCollision(entityRecHitBox[j].body);
            if (hit == true) {
                checkCollisionType(entityRecHitBox[i].entityType, entityRecHitBox[j].entityType);
            }
        }
    }

    for (size_t i = 0; i <= entityCirHitBox.size(); i++) {
        for (size_t j = 0; j <= entityCirHitBox.size(); j++) {
            hit = entityCirHitBox[i].checkCollision(entityCirHitBox[j].dot);
            if (hit == true) {
                checkCollisionType(entityCirHitBox[i].entityType, entityCirHitBox[j].entityType);
            }
        }
    }

    for (size_t i = 0; i <= entityRecHitBox.size(); i++) {
        for (size_t j = 0; j <= entityCirHitBox.size(); j++) {
            hit = entityRecHitBox[i].checkCollision(entityCirHitBox[j].dot);
            if (hit == true) {
                checkCollisionType(entityRecHitBox[i].entityType, entityCirHitBox[j].entityType);
            }
        }
    }
}


void CollisionManager::checkCollisionType(EntityType type1, EntityType type2) {
    if ((type1 == PLAYER && type2 == SLIME) || (type1 == SLIME && type2 == PLAYER)) {
        //player gets hit by slime
    }
    if ((type1 == PLAYER && type2 == PILLAR) || (type1 == PILLAR && type2 == PLAYER)) {
        //player hits an object
    }
}