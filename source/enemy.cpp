#include "../header/enemy.h"

Enemy::Enemy() : 
    movementSpeed(220.0f), bestDirection(sf::Vector2f(0.0f, 0.0f))
{
    //generate 16 directions
    generateDirections();
    //load up all enemy texture
    loadTexture("slime", "assets/slime.png");
}

void Enemy::loadTexture(const std::string& name, const std::string& filePath) {
    sf::Texture texture;
    if (texture.loadFromFile(filePath)) {
        enemyTextures[name] = texture;
    } else {
        throw std::runtime_error ("Failed to laod enemy texture");
    }
}

//generates all the directions of possible movement
void Enemy::generateDirections(int numDirections) {
    const float zeroTreshhold = 1e-6; //to stop floating point precission eeror
    directions.clear();
    for (int i = 0; i < numDirections; i++) {
        float angle = 2 * M_PI * i / numDirections;
        float x = std::cos(angle);
        float y = std::sin(angle);
        if (std::abs(x) < zeroTreshhold) x = 0;
        if (std::abs(y) < zeroTreshhold) y = 0;
        directions.push_back(sf::Vector2f(x, y));
    }
}

void Enemy::maleeMovement(const sf::Vector2f& target) {
    sf::Vector2f toTarget = target - enemySprite.getPosition();
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
    enemySprite.move(move);
}