#pragma once
#include "utility.h"

class Collision {
protected:

public:
    Collision() = default;
    virtual ~Collision() = default;
    virtual void updateSize(const sf::IntRect& bodyDim) = 0;
    virtual void followEntity(const sf::Vector2f& entityPosition) = 0;
    //collision check AABB-CIRCLE
    static bool checkCollision(const sf::Shape& body1, const sf::Shape& body2);
};

//AABB
class BoxCollision : public Collision {
private:
public:
    sf::RectangleShape body;
    //constructor
    BoxCollision();
    //functions
    virtual void updateSize(const sf::IntRect& bodyDim) override;
    virtual void followEntity(const sf::Vector2f& entityPosition) override;
    static bool checkCollision(const sf::Shape& body1, const sf::Shape& body2);
};

class CircleCollision : public Collision {
private:
public:
    sf::CircleShape body;
    //constructor
    CircleCollision();
    //functions
    virtual void updateSize(const sf::IntRect& bodyDim) override;
    virtual void followEntity(const sf::Vector2f& entityPosition) override;
    static bool checkCollision(const sf::Shape& body1, const sf::Shape& body2);
};

class SlashShape {
private:
    float theta; 
    
public:
    sf::VertexArray slash; 
    SlashShape();  

    sf::VertexArray createSlashShape(float centerX, float centerY, float outerRadius, float arcAngle, float rotationAngle);
    sf::FloatRect getBounds(const sf::VertexArray& vertexArray);  
    bool slashRectangleCheck(const sf::VertexArray& slashShape, const sf::RectangleShape& other);
    bool slashCircleCheck(const sf::VertexArray& slashShape, const sf::CircleShape& circle);
};