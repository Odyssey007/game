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
    float xPosition, yPosition, distance;

    xPosition = std::max(boxPosition.x, std::min(circlePosition.x, boxPosition.x + body.getSize().x));
    yPosition = std::max(boxPosition.y, std::min(circlePosition.y, boxPosition.y + body.getSize().y));

    distance = std::sqrt(std::pow(xPosition - circlePosition.x, 2) + std::pow(yPosition - circlePosition.y, 2));

    if (distance <= other.getRadius()) {
        return true;
    }
    return false;
}