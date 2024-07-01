#include "../header/collision.h"

RecCollision::RecCollision() {
    body.setOutlineColor(sf::Color::Red);
    body.setOutlineThickness(1.0f);
    body.setFillColor(sf::Color::Transparent);
}


void RecCollision::updateSize(const sf::IntRect& bodyDim) {
    body.setSize(sf::Vector2f(bodyDim.width, bodyDim.height));
    body.setOrigin(sf::Vector2f(bodyDim.width/2.0f, bodyDim.height/2.0f));
    
}

void RecCollision::followEntity(const sf::Vector2f& entityPosition) {
    body.setPosition(entityPosition);
}

bool RecCollision::checkCollision(const sf::RectangleShape& other) const {
    return body.getGlobalBounds().intersects(other.getGlobalBounds()); 
}

bool RecCollision::checkCollision(const sf::CircleShape& other) const {
    sf::Vector2f boxPosition = body.getPosition();
    sf::Vector2f circlePosition = other.getPosition();
    sf::Vector2f boxSize = body.getSize();

    // Adjust the box position to account for its origin
    boxPosition.x -= body.getOrigin().x;
    boxPosition.y -= body.getOrigin().y;

    // Calculate the closest point on the rectangle to the center of the circle
    float closestX = std::max(boxPosition.x, std::min(circlePosition.x, boxPosition.x + boxSize.x));
    float closestY = std::max(boxPosition.y, std::min(circlePosition.y, boxPosition.y + boxSize.y));

    // Calculate the distance between the circle's center and this closest point
    float distanceX = closestX - circlePosition.x;
    float distanceY = closestY - circlePosition.y;

    // Calculate the squared distance and compare it to the squared radius to avoid computing the square root
    float distanceSquared = distanceX * distanceX + distanceY * distanceY;
    float radiusSquared = other.getRadius() * other.getRadius();

    // If the squared distance is less than the squared radius, there is a collision
    return distanceSquared <= radiusSquared;
}

CircleCollision::CircleCollision() {
    dot.setOutlineThickness(1.0f);
    dot.setOutlineColor(sf::Color::Red);
    dot.setFillColor(sf::Color::Transparent); 
}

// class CircleCollision functions
void CircleCollision::updateCircle(const sf::IntRect & dotDimension) {
    dot.setRadius(dotDimension.width/2.0f);
    dot.setOrigin(sf::Vector2f(dotDimension.width/2.0f, dotDimension.width/2.0f));
}

void CircleCollision::followEntity(const sf::Vector2f& entityPosition) {
    dot.setPosition(entityPosition);
}