#pragma once
#include "utility.h"

class CollisionManager {
    
};

class RecCollision {
private:
    
public:
    sf::RectangleShape body;
    sf::CircleShape dot; 

    RecCollision();
    void updateSize(const sf::IntRect& bodyDim);
    void circleUpdate(const sf::IntRect& dotDim);
    void followEntity(const sf::Vector2f& entityPosition);

    bool checkCollision(const sf::RectangleShape& other) const;
    bool checkCollision(const sf::CircleShape& other) const;
};