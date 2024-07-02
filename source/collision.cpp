#include "../header/collision.h"

//COLLISION CHECK BETWEEN BOX-CIRCLE || CIRCLE-BOX
bool Collision::checkCollision(const sf::RectangleShape& b1, const sf::CircleShape& b2) {
    sf::Vector2f boxPosition = b1.getPosition() - b1.getOrigin();
    sf::Vector2f circlePosition = b2.getPosition();
    sf::Vector2f bodySize = b1.getSize();
    float radius = b2.getRadius();
    float closetX, closetY, distance;

    closetX = std::max(boxPosition.x, std::min(circlePosition.x, boxPosition.x + bodySize.x));
    closetY = std::max(boxPosition.y, std::min(circlePosition.y, boxPosition.y + bodySize.y));

    closetX = (closetX - circlePosition.x)*(closetX - circlePosition.x);
    closetY = (closetY - circlePosition.y)*(closetY - circlePosition.y);

    distance = closetX + closetY;
    radius = radius*radius;

    return distance <= radius;
}

//AABB HITBOX
BoxCollision::BoxCollision(EntityType type) {
    body.setOutlineColor(sf::Color::Red);
    body.setOutlineThickness(1.0f);
    body.setFillColor(sf::Color::Transparent);

    entityType = type;
    collisionType = AABB;
}

void BoxCollision::updateSize(const sf::IntRect& bodyDim) {
    body.setSize(sf::Vector2f(bodyDim.width, bodyDim.height));
    body.setOrigin(sf::Vector2f(bodyDim.width/2.0f, bodyDim.height/2.0f));
}

void BoxCollision::followEntity(const sf::Vector2f& entityPosition) {
    body.setPosition(entityPosition);
}

//COLLISION CHECK BETWEEN BOX-BOX
bool BoxCollision::checkCollision(const sf::RectangleShape& other) const {
    return body.getGlobalBounds().intersects(other.getGlobalBounds()); 
}

//CIRCLE HITBOX
CircleCollision::CircleCollision(EntityType type) {
    //visual
    body.setOutlineThickness(1.0f);
    body.setOutlineColor(sf::Color::Red);
    body.setFillColor(sf::Color::Transparent); 

    entityType = type;
    collisionType = CIRCLE;
}

void CircleCollision::updateSize(const sf::IntRect & bodyDim) {
    body.setRadius(bodyDim.width/2.0f);
    body.setOrigin(sf::Vector2f(bodyDim.width/2.0f, bodyDim.width/2.0f));
}

void CircleCollision::followEntity(const sf::Vector2f& entityPosition) {
    body.setPosition(entityPosition);
}

//COLLISION CHECK BETWEEN CIRCLE-CIRCLE
bool CircleCollision::checkCollision(const sf::CircleShape& other) const {
    return body.getGlobalBounds().intersects(other.getGlobalBounds());
}

 // class slashShape function
SlashShape::SlashShape() 
    :theta(0.0f),
     slash(sf::TriangleFan)
     {}

sf::VertexArray SlashShape::createSlashShape(float centerX, float centerY, float outerRadius, float arcAngle, float rotationAngle){
    slash.clear(); 
    slash.append(sf::Vertex(sf::Vector2f(centerX, centerY), sf::Color::Red));

    for(int i = 0; i <= 20; i++) {
        theta = -arcAngle/2.0f + (i/20.0f) *arcAngle + rotationAngle; 
        float x = centerX + outerRadius*cos(theta);
        float y = centerY + outerRadius*sin(theta); 
        slash.append(sf::Vertex(sf::Vector2f(x, y), sf::Color::Red)); 
    }  
    return slash; 
}

sf::FloatRect SlashShape::getBounds(const sf::VertexArray& vertexArray){
    if(vertexArray.getVertexCount() == 0) {
        return sf::FloatRect(); 
    }

    float minX = vertexArray[0].position.x;
    float maxX = vertexArray[0].position.x;
    float minY = vertexArray[0].position.y;
    float maxY = vertexArray[0].position.y;

    for (size_t i = 1; i < vertexArray.getVertexCount(); i++) {
        sf::Vector2f pos = vertexArray[i].position;
        if (pos.x < minX) minX = pos.x;
        if (pos.x > maxX) maxX = pos.x;
        if (pos.y < minY) minY = pos.y;
        if (pos.y > maxY) maxY = pos.y;
    }

    return sf::FloatRect(minX, minY, maxX - minX, maxY - minY);
}

bool SlashShape::slashRectangleCheck(const sf::VertexArray& slashShape, const sf::RectangleShape& other) {
    sf::FloatRect slashBounds = getBounds(slashShape); 
    sf::FloatRect rectangleBounds = other.getGlobalBounds(); 
    return slashBounds.intersects(rectangleBounds); 
}

bool SlashShape::slashCircleCheck(const sf::VertexArray& slashShape, const sf::CircleShape& circle) {
    sf::FloatRect slashBounds = getBounds(slashShape);
    sf::FloatRect circleBounds = circle.getGlobalBounds();
    return slashBounds.intersects(circleBounds);
}
