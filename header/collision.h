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
    void checkCollision();
    void circleSize(const sf:: IntRect& dotDimension);
};

class CircleCollision {
    private:

    public:
        sf::CircleShape dot; 

        CircleCollision();
        void updateCircle(const sf::IntRect& dotDimension);
        void followEntity(const sf::Vector2f& entityPosition);
        //bool collisionCheckC(const sf::IntRect& first, const sf::IntRect& second);
        bool collisionCheckC(const sf::CircleShape& circle);
};