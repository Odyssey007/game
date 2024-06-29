#pragma once
#include "utility.h"

class RecCollision {
private:
    
public:
    sf::RectangleShape body;

    RecCollision();
    void updateSize(const sf::IntRect& bodyDim);

    void followEntity(const sf::Vector2f& entityPosition);
    void checkCollision();
};