#pragma once
#include "utility.h"

enum EntityType { PLAYER, SLIME, PILLAR };

enum CollisionType { AABB, CIRCLE, SLASH};

class Collision {
protected:

public:
    EntityType entityType;
    CollisionType collisionType;

    virtual ~Collision() = default;
    //virtual const CollisionType* getType() const = 0;
    virtual void updateSize(const sf::IntRect& bodyDim) = 0;
    virtual void followEntity(const sf::Vector2f& entityPosition) = 0;

    static bool checkCollision(const sf::RectangleShape& b1, const sf::CircleShape& b2);
};

class BoxCollision : public Collision {
private:
    
public:
    sf::RectangleShape body;

    BoxCollision() = default;
    BoxCollision(EntityType type);

    virtual void updateSize(const sf::IntRect& bodyDim) override;
    virtual void followEntity(const sf::Vector2f& entityPosition) override;
    bool checkCollision(const sf::RectangleShape& other) const;
};

class CircleCollision : public Collision {
    private:

    public:
    sf::CircleShape body; 

    CircleCollision() = default;
    CircleCollision(EntityType type);

    virtual void updateSize(const sf::IntRect& bodyDim) override;
    virtual void followEntity(const sf::Vector2f& entityPosition) override;
    bool checkCollision(const sf::CircleShape& other) const;
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
