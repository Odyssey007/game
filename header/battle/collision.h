#pragma once
#include "../header/utility.h"

class Collision {
public:
    Collision() = default;
    virtual ~Collision() = default;
    virtual void updateSize(const sf::FloatRect& bodyDim) = 0;
    virtual void followEntity(const sf::Vector2f& entityPosition) = 0;
    virtual sf::Vector2f getPosition() const = 0;
    virtual sf::FloatRect getBounds() const = 0;
    //collision check AABB-CIRCLE
    static bool checkCollision(const sf::FloatRect& boxBounds, const sf::FloatRect& circleBounds);
    static sf::Vector2f calcDistance(sf::FloatRect boxBounds, sf::Vector2f circleCenter, float radius);
};

//AABB
class BoxCollision : public Collision {
private:
    sf::RectangleShape body;
public:
    //constructor
    BoxCollision();
    //functions
    virtual void updateSize(const sf::FloatRect& bodyDim) override;
    virtual void followEntity(const sf::Vector2f& entityPosition) override;
    static bool checkCollision(const sf::FloatRect& bounds1, const sf::FloatRect& bounds2);
    //fetchers
    virtual sf::Vector2f getPosition() const override;
    virtual sf::FloatRect getBounds() const override;
};

class CircleCollision : public Collision {
private:
    sf::CircleShape body;
public:
    //constructor
    CircleCollision();
    //functions
    virtual void updateSize(const sf::FloatRect& bodyDim) override;
    virtual void followEntity(const sf::Vector2f& entityPosition) override;
    static bool checkCollision(const sf::FloatRect& bounds1, const sf::FloatRect& bounds2);
    //fetchers
    virtual sf::Vector2f getPosition() const override;
    virtual sf::FloatRect getBounds() const override;
};

// *not used -----------------
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