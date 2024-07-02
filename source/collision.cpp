#include "../header/collision.h"

//COLLISION CHECK BETWEEN BOX-CIRCLE || CIRCLE-BOX
bool Collision::checkCollision(const sf::Shape& body1, const sf::Shape& body2) {
    sf::Vector2f boxPosition = body1.getPosition() - body1.getOrigin();
    sf::Vector2f circlePosition = body2.getPosition();
    sf::Vector2f bodySize = sf::Vector2f(body1.getGlobalBounds().width, body1.getGlobalBounds().height);
    float radius = body2.getGlobalBounds().width/2.0f;
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
BoxCollision::BoxCollision() {
    //visual
    body.setOutlineColor(sf::Color::Red);
    body.setOutlineThickness(1.0f);
    body.setFillColor(sf::Color::Transparent);
}

void BoxCollision::updateSize(const sf::IntRect& bodyDim) {
    body.setSize(sf::Vector2f(bodyDim.width, bodyDim.height));
    body.setOrigin(sf::Vector2f(bodyDim.width/2.0f, bodyDim.height/2.0f));
}

void BoxCollision::followEntity(const sf::Vector2f& entityPosition) {
    body.setPosition(entityPosition);
}

//collision check BOX-BOX
bool BoxCollision::checkCollision(const sf::Shape& body1, const sf::Shape& body2) {
    return body1.getGlobalBounds().intersects(body2.getGlobalBounds());
}

//CIRCLE HITBOX
CircleCollision::CircleCollision() {
    //visual
    body.setOutlineThickness(1.0f);
    body.setOutlineColor(sf::Color::Red);
    body.setFillColor(sf::Color::Transparent); 

}

void CircleCollision::updateSize(const sf::IntRect & bodyDim) {
    body.setRadius(bodyDim.width/2.0f);
    body.setOrigin(sf::Vector2f(bodyDim.width/2.0f, bodyDim.width/2.0f));
}

void CircleCollision::followEntity(const sf::Vector2f& entityPosition) {
    body.setPosition(entityPosition);
}

//collision check CIRCLE-CIRCLE
bool CircleCollision::checkCollision(const sf::Shape& body1, const sf::Shape& body2) {
    return body1.getGlobalBounds().intersects(body2.getGlobalBounds());
}