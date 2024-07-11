#include "../header/collision.h"

//COLLISION CHECK BETWEEN BOX-CIRCLE || CIRCLE-BOX
bool Collision::checkCollision(const sf::Shape& body1, const sf::Shape& body2) {
    sf::FloatRect circleBounds = body2.getGlobalBounds();
    float radius = circleBounds.width / 2.0f;
    sf::Vector2f circleCenter(circleBounds.left + radius, circleBounds.top + radius);
    sf::FloatRect boxBounds = body1.getGlobalBounds();

    sf::Vector2f distanceVector = calcDistance(boxBounds, circleCenter, radius);
    float distance = magnitude(distanceVector);

    return distance <= radius;
}

sf::Vector2f Collision::calcDistance(sf::FloatRect boxBounds, sf::Vector2f circleCenter, float radius) {
    float closetX, closetY, distance;

    closetX = std::max(boxBounds.left, std::min(circleCenter.x, boxBounds.left + boxBounds.width));
    closetY = std::max(boxBounds.top, std::min(circleCenter.y, boxBounds.top + boxBounds.height));

    sf::Vector2f distanceVector = circleCenter - sf::Vector2f(closetX, closetY);

    return distanceVector;
}

//AABB HITBOX
BoxCollision::BoxCollision() {
    //visual
    body.setOutlineColor(sf::Color::Red);
    body.setOutlineThickness(1.0f);
    body.setFillColor(sf::Color::Transparent);
}

void BoxCollision::updateSize(const sf::FloatRect& bodyDim) {
    body.setSize(sf::Vector2f(bodyDim.width, bodyDim.height));
    body.setOrigin(sf::Vector2f(bodyDim.width/2.0f, bodyDim.height/2.0f));
}

void BoxCollision::followEntity(const sf::Vector2f& entityPosition) {
    body.setPosition(entityPosition);
}

//collision check BOX-BOX
bool BoxCollision::checkCollision(const sf::Shape& body1, const sf::Shape& body2) {
    return body1.getGlobalBounds().intersects(body2.getGlobalBounds());
}

//CIRCLE HITBOX
CircleCollision::CircleCollision() {
    //visual
    body.setOutlineThickness(1.0f);
    body.setOutlineColor(sf::Color::Red);
    body.setFillColor(sf::Color::Transparent); 

}

void CircleCollision::updateSize(const sf::FloatRect & bodyDim) {
    body.setRadius(bodyDim.width/2.0f);
    body.setOrigin(sf::Vector2f(bodyDim.width/2.0f, bodyDim.width/2.0f));
}

void CircleCollision::followEntity(const sf::Vector2f& entityPosition) {
    body.setPosition(entityPosition);
}

//collision check CIRCLE-CIRCLE
bool CircleCollision::checkCollision(const sf::Shape& body1, const sf::Shape& body2) {
    return body1.getGlobalBounds().intersects(body2.getGlobalBounds());
}

//SLASH
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