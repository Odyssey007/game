#include "../header/collision.h"


RecCollision::RecCollision() {
    body.setOutlineColor(sf::Color::Red);
    body.setOutlineThickness(1.0f);
    body.setFillColor(sf::Color::Transparent);
}

CircleCollision::CircleCollision() {
    dot.setOutlineThickness(1.0f);
    dot.setOutlineColor(sf::Color::Red);
    dot.setFillColor(sf::Color::Transparent); 
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


// class CircleCollision functions
void CircleCollision::updateCircle(const sf::IntRect & dotDimension) {
    dot.setRadius(dotDimension.width/2.0f);
    dot.setOrigin(sf::Vector2f(dotDimension.width/2.0f, dotDimension.width/2.0f));
}

void CircleCollision::followEntity(const sf::Vector2f& entityPosition) {
    dot.setPosition(entityPosition);
}