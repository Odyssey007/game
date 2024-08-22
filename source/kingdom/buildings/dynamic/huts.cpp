#include "../header/kingdom/buildings/dynamic/huts.h"

Huts::Huts() {
    hutRect.left = 700.0f;
    hutRect.top = 700.0f;
    hutRect.width = 75.0f; 
    hutRect.height = 150.0f;
}

void Huts::moveBuilding(float x, float y) {
    hutRect.left = x; 
    hutRect.top = y; 
}

void Huts::upgrade() {
    //- Upgrade logic for castle goes here. 
}

sf::Vector2f Huts::bottomMid() {
    return sf::Vector2f (hutRect.left + (hutRect.width/2), hutRect.top + hutRect.height + 5); 
}

void Huts::render(sf::RenderWindow& window) {
    sf::RectangleShape drawRect; 
    drawRect.setOutlineColor(sf::Color::Red); 
    drawRect.setOutlineThickness(1.0f); 
    drawRect.setFillColor(sf::Color::Transparent); 
    drawRect.setSize(sf::Vector2f(hutRect.width, hutRect.height)); 
    drawRect.setPosition(hutRect.left, hutRect.top);

    window.draw(drawRect); 
}