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


// class CircleCollision functions
void CircleCollision::updateCircle(const sf::IntRect & dotDimension) {
    dot.setRadius(dotDimension.width/2.0f);
    dot.setOrigin(sf::Vector2f(dotDimension.width/2.0f, dotDimension.width/2.0f));
}

void CircleCollision::followEntity(const sf::Vector2f& entityPosition) {
    dot.setPosition(entityPosition);
}

// bool CircleCollision::collisionCheckC(const sf::IntRect& first, const sf::IntRect& second){
//     sf::Vector2f firstOrigin (first.width/2.0f, first.width/2.0f); 
//     sf::Vector2f secondOrigin (second.width/2.0f, second.width/2.0f); 
//     float diameter = (first.width/2.0f) + (second.width/2.0f); 

//     float length = distance({firstOrigin.x, firstOrigin.y}, {secondOrigin.x, secondOrigin.y}); 
//     if(length <= diameter){
//         return false; 
//     }
//     else {
//         return true; 
//     }
// }

 bool CircleCollision::collisionCheckC(const sf::CircleShape& circle) {
     return dot.getGlobalBounds().intersects(circle.getGlobalBounds());
 }
