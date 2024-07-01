#include "../header/collision.h"

RecCollision::RecCollision() {
    body.setOutlineColor(sf::Color::Red);
    body.setOutlineThickness(1.0f);
    body.setFillColor(sf::Color::Transparent);
}

void RecCollision::updateSize(const sf::IntRect& bodyDim) {
    body.setSize(sf::Vector2f(bodyDim.width, bodyDim.height));
    body.setOrigin(sf::Vector2f(bodyDim.width/2.0f, bodyDim.height/2.0f));  
}

void RecCollision::followEntity(const sf::Vector2f& entityPosition) {
    body.setPosition(entityPosition);
}

bool RecCollision::checkCollision(const sf::RectangleShape& other) const {
    return body.getGlobalBounds().intersects(other.getGlobalBounds()); 
}

bool RecCollision::checkCollision(const sf::CircleShape& other) const {
    sf::Vector2f boxPosition = body.getPosition();
    sf::Vector2f circlePosition = other.getPosition();
    float xPosition, yPosition, distance;

    xPosition = std::max(boxPosition.x, std::min(circlePosition.x, boxPosition.x + body.getSize().x));
    yPosition = std::max(boxPosition.y, std::min(circlePosition.y, boxPosition.y + body.getSize().y));

    distance = std::sqrt(std::pow(xPosition - circlePosition.x, 2) + std::pow(yPosition - circlePosition.y, 2));

    if (distance <= other.getRadius()) {
        return true;
    }
    return false;
}


// class CircleCollision functions
CircleCollision::CircleCollision() {
    dot.setOutlineThickness(1.0f);
    dot.setOutlineColor(sf::Color::Red);
    dot.setFillColor(sf::Color::Transparent); 
}

void CircleCollision::updateCircle(const sf::IntRect & dotDimension) {
    dot.setRadius(dotDimension.width/2.0f);
    dot.setOrigin(sf::Vector2f(dotDimension.width/2.0f, dotDimension.width/2.0f));
}

void CircleCollision::followEntity(const sf::Vector2f& entityPosition) {
    dot.setPosition(entityPosition);
}

 bool CircleCollision::collisionCheckC(const sf::CircleShape& circle) {
     return dot.getGlobalBounds().intersects(circle.getGlobalBounds());
 }


 // class slashShape function
SlashShape::SlashShape() 
    :theta(0.0f),
     slash(sf::TriangleFan)
     {}

sf::VertexArray SlashShape::createSlashShape(float centerX, float centerY, float outerRadius, float arcAngle){
    slash.clear(); 
    slash.append(sf::Vertex(sf::Vector2f(centerX, centerY), sf::Color::Red));

    for(int i = 0; i <= 20; i++){
        theta = -arcAngle/2.0f + (i/20.0f) *arcAngle; 
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