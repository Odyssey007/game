#include "../header/enemy.h"

Enemy::Enemy() {
    //preliminaries
    entityType = ENEMY;
    loadTexture("slime", "assets/slime.png"); //load up slime into textures
    //movement set up
    movementSpeed = 200.0f; baseDamage = 5.0f;
    bestDirection = sf::Vector2f(0.0f, 0.0f);
    generateDirections();
}

void Enemy::loadTexture(const std::string& name, const std::string& filePath) {
    sf::Texture texture;
    if (texture.loadFromFile(filePath)) {
        textures[name] = texture;
    } else {
        throw std::runtime_error ("Failed to load enemy texture");
    }
}

//generates all the directions of possible movement
void Enemy::generateDirections(int numDirections) {
    const float zeroThreshold = 1e-6; //to stop floating point precision error
    directions.clear();
    for (int i = 0; i < numDirections; i++) {
        float angle = 2 * M_PI * i / numDirections;
        float x = std::cos(angle);
        float y = std::sin(angle);
        if (std::abs(x) < zeroThreshold) x = 0;
        if (std::abs(y) < zeroThreshold) y = 0;
        directions.push_back(sf::Vector2f(x, y));
    }
}

void Enemy::meleeMovement(const sf::Vector2f& target) {
    sf::Vector2f toTarget = target - sprite.getPosition();
    toTarget = normalize(toTarget);
    //finds the optimal direction toward target 
    float maxDot = -1.0f;
    for (int i = 0; i < 16; i++) {
        float dot = dotProduct(directions[i], toTarget);
        if (dot > maxDot) {
            maxDot = dot;
            bestDirection = directions[i];
        }
    }
    sf::Vector2f move = bestDirection*movementSpeed*DeltaTime::getInstance()->getDeltaTime();
    sprite.move(move);
}

void Enemy::initialPosition() {
    //!
}

void Enemy::handleCollisions(Entity& other) {
    //!
}