#pragma once
#include "utility.h"


class RecCollision {
private:
    
public:
    sf::RectangleShape body;
    sf::CircleShape dot;

    RecCollision();
    void updateSize(const sf::IntRect& bodyDim);
    void followEntity(const sf::Vector2f& entityPosition);
    bool checkCollision(const sf::RectangleShape& other) const;
    bool checkCollision(const sf::CircleShape& other) const;
};

class CircleCollision {
    private:

    public:
    sf::CircleShape dot; 

    CircleCollision();
    void updateCircle(const sf::IntRect& dotDimension);
    void followEntity(const sf::Vector2f& entityPosition);
};

class CollisionManager {
private:

public:
    std::vector <RecCollision> entityRecHitBox;
    std::vector <CircleCollision> entityCirHitBox;
};
