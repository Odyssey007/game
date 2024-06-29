#include "../header/collision.h"


RecCollision::RecCollision() {
    body.setOutlineColor(sf::Color::Red);
    body.setOutlineThickness(3.0f);
    body.setFillColor(sf::Color::Transparent);
}

void RecCollision::updateSize(const sf::IntRect& bodyDim) {
    body.setSize(sf::Vector2f(bodyDim.width, bodyDim.height));
    body.setOrigin(sf::Vector2f(bodyDim.width/2.0f, bodyDim.height/2.0f));
    
}

void RecCollision::followEntity(const sf::Vector2f& entityPosition) {
    body.setPosition(entityPosition);
}

void RecCollision::checkCollision() {
    
}