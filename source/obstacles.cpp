#include "../header/obstacles.h"

StaticObstacle::StaticObstacle() {
    //preliminaries
    entityType = OBSTACLE; collisionType = AABB;
    //?temporary => set up texture
    obstacle.setFillColor(sf::Color::Blue);
    obstacle.setSize(sf::Vector2f(25.0f, 100.0f));
    obstacle.setOrigin(sf::Vector2f(25.0f/2.0f, 50.0f));
    //hitbox
    bounds = sf::IntRect(0, 0, 25, 100);
    hitBox.updateSize(bounds);
    //set initial position
    initialPosition();
}

void StaticObstacle::render(sf::RenderWindow& window) {
    window.draw(obstacle);
    window.draw(hitBox.body);
}

void StaticObstacle::initialPosition() {
    obstacle.setPosition(400, 400);
    hitBox.body.setPosition(400, 400);
}

size_t StaticObstacle::getState() {
    return 1;
}

sf::Shape& StaticObstacle::getShape() {
    return hitBox.body;
}

void StaticObstacle::handleCollisions(Entity& other) {
    if (other.collisionType == AABB) {

    } else if (other.collisionType == CIRCLE) {

    }
}
