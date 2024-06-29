#pragma once
#include "utility.h"

class RecCollision {
private:
    sf::RectangleShape body;

    void update(const sf::Vector2f& );
public:
    RecCollision(const sf::Vector2f& bodyDim);
};