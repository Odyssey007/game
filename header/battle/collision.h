#pragma once
#include "../header/battle/utility.h"

class Collision {
protected:

public:
    Collision() = default;
    virtual ~Collision() = default;
    virtual void updateSize(const sf::FloatRect& bodyDim) = 0;
    virtual void followEntity(const sf::Vector2f& entityPosition) = 0;
    //collision check AABB-CIRCLE
    static bool checkCollision(const sf::FloatRect& boxBounds, const sf::FloatRect& circleBounds);
    static sf::Vector2f calcDistance(sf::FloatRect boxBounds, sf::Vector2f circleCenter, float radius);
};

//AABB
class BoxCollision : public Collision {
private:
public:
    sf::RectangleShape body;
    //constructor
    BoxCollision();
    //functions
    virtual void updateSize(const sf::FloatRect& bodyDim) override;
    virtual void followEntity(const sf::Vector2f& entityPosition) override;
    static bool checkCollision(const sf::FloatRect& bounds1, const sf::FloatRect& bounds2);
};

class CircleCollision : public Collision {
private:
public:
    sf::CircleShape body;
    //constructor
    CircleCollision();
    //functions
    virtual void updateSize(const sf::FloatRect& bodyDim) override;
    virtual void followEntity(const sf::Vector2f& entityPosition) override;
    static bool checkCollision(const sf::FloatRect& bounds1, const sf::FloatRect& bounds2);
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