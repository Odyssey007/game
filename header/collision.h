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
        bool collisionCheckC(const sf::CircleShape& circle);
};

class SlashShape {
    private:
        float theta; 
        
    public:
        sf::VertexArray slash; 
        SlashShape();  

        sf::VertexArray createSlashShape(float centerX, float centerY, float outerRadius, float arcAngle);
        sf::FloatRect getBounds(const sf::VertexArray& vertexArray);  
        bool slashRectangleCheck(const sf::VertexArray& slashShape, const sf::RectangleShape& other);
        bool slashCircleCheck(const sf::VertexArray& slashShape, const sf::CircleShape& circle);
};
