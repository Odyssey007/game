#include <../header/enemy.h>
#include <cmath>

Enemy::Enemy() {
    //loads the sime texture
    if (!this->slime_texture.loadFromFile("../assets/slime.png")) {
        throw std::runtime_error ("Failed to load player texture");
    }
    this->slime_sprite.setTexture(slime_texture);
    //generates all the directions of movement
    generateDirections();
}
#include <iostream>

float dotProduct(const sf::Vector2f& one, const sf::Vector2f& two) {
    return one.x*two.x + one.y*two.y;
}

sf::Vector2f normalize(sf::Vector2f& one) {    
    float normal = sqrt(one.x*one.x + one.y*one.y);
    if (normal != 0) {
        return one /= normal;
    } else {
        return one;
    }
}

void Enemy::generateDirections(int numDirections) {
    const float zeroTreshhold = 1e-6; //to stop floating point precission eeror
    float startAngle = 2 * M_PI / numDirections;
    for (int i = 0; i < numDirections; i++) {
        float angle = startAngle * i;
        float x = std::cos(angle);
        float y =  std::sin(angle);
        if (std::abs(x) < zeroTreshhold) x = 0;
        if (std::abs(y) < zeroTreshhold) y = 0;
        directions.push_back(sf::Vector2f(x, y));
    }
}

void Enemy::movement(const sf::Vector2f& target) {
    sf::Vector2f toTarget = target - slime_sprite.getPosition();
    
    if (toTarget.x >= 150 || toTarget.y >= 150 || toTarget.x <= -150 || toTarget.y <= -150) {
        toTarget = normalize(toTarget);

        float maxDot = -1.0f;
        sf::Vector2f bestDirection;
        for (int i = 0; i < 16; i++) {
            float dot = dotProduct(directions[i], toTarget);
            if (dot > maxDot) {
                maxDot = dot;
                bestDirection = directions[i];
            }
        }

        slime_sprite.move(bestDirection*movementSpeed*sf::seconds(1.0f / 60.0f).asSeconds());
    }
}