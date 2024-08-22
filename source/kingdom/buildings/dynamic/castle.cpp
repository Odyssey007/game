#include "../header/kingdom/buildings/dynamic/castle.h"

Castle::Castle() {
    //? Will have to set up castle sprite here. 
    castleRect.left = 50.0f;
    castleRect.top = 50.0f;
    castleRect.width = 500.0f; 
    castleRect.height = 400.0f; 
}

void Castle::moveBuilding(float x, float y) {
    castleRect.left = x; 
    castleRect.top = y; 
}

void Castle::upgrade() {
    //- Upgrade logic for castle goes here. 
}

sf::Vector2f Castle::bottomMid() {
    return sf::Vector2f (castleRect.left + (castleRect.width/2), castleRect.top + castleRect.height + 5); 
}

void Castle::render(sf::RenderWindow& window) {
    sf::RectangleShape drawRect; 
    drawRect.setOutlineColor(sf::Color::Red); 
    drawRect.setOutlineThickness(1.0f); 
    drawRect.setFillColor(sf::Color::Transparent); 
    drawRect.setSize(sf::Vector2f(castleRect.width, castleRect.height)); 
    drawRect.setPosition(castleRect.left, castleRect.top);

    window.draw(drawRect); 
}