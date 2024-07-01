#include "collision.h"

class CollisionManager {
private:
    std::vector<RecCollision> entityRecHitBox;
    std::vector<CircleCollision> entityCirHitBox;
public:

    template <typename T>
    void addEntity(T entity);
    void checkCollisions();
    void checkCollisionType(EntityType type1, EntityType type2);
    void handleCollision();
};