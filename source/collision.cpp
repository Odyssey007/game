#include "../header/collision.h"

//COLLISION CHECK BETWEEN BOX-CIRCLE || CIRCLE-BOX
bool Collision::checkCollision(const sf::RectangleShape& b1, const sf::CircleShape& b2) {
    sf::Vector2f boxPosition = b1.getPosition() - b1.getOrigin();
    sf::Vector2f circlePosition = b2.getPosition();
    sf::Vector2f bodySize = b1.getSize();
    float radius = b2.getRadius();
    float closetX, closetY, distance;

    closetX = std::max(boxPosition.x, std::min(circlePosition.x, boxPosition.x + bodySize.x));
    closetY = std::max(boxPosition.y, std::min(circlePosition.y, boxPosition.y + bodySize.y));

    closetX = (closetX - circlePosition.x)*(closetX - circlePosition.x);
    closetY = (closetY - circlePosition.y)*(closetY - circlePosition.y);

    distance = closetX + closetY;
    radius = radius*radius;

    return distance <= radius;
}

//AABB HITBOX
BoxCollision::BoxCollision(EntityType type) {
    body.setOutlineColor(sf::Color::Red);
    body.setOutlineThickness(1.0f);
    body.setFillColor(sf::Color::Transparent);

    entityType = type;
    collisionType = AABB;
}

void BoxCollision::updateSize(const sf::IntRect& bodyDim) {
    body.setSize(sf::Vector2f(bodyDim.width, bodyDim.height));
    body.setOrigin(sf::Vector2f(bodyDim.width/2.0f, bodyDim.height/2.0f));
}

void BoxCollision::followEntity(const sf::Vector2f& entityPosition) {
    body.setPosition(entityPosition);
}

//COLLISION CHECK BETWEEN BOX-BOX
bool BoxCollision::checkCollision(const sf::RectangleShape& other) const {
    return body.getGlobalBounds().intersects(other.getGlobalBounds()); 
}

//CIRCLE HITBOX
CircleCollision::CircleCollision(EntityType type) {
    //visual
    body.setOutlineThickness(1.0f);
    body.setOutlineColor(sf::Color::Red);
    body.setFillColor(sf::Color::Transparent); 

    entityType = type;
    collisionType = CIRCLE;
}

void CircleCollision::updateSize(const sf::IntRect & bodyDim) {
    body.setRadius(bodyDim.width/2.0f);
    body.setOrigin(sf::Vector2f(bodyDim.width/2.0f, bodyDim.width/2.0f));
}

void CircleCollision::followEntity(const sf::Vector2f& entityPosition) {
    body.setPosition(entityPosition);
}

//COLLISION CHECK BETWEEN CIRCLE-CIRCLE
bool CircleCollision::checkCollision(const sf::CircleShape& other) const {
    return body.getGlobalBounds().intersects(other.getGlobalBounds());
}