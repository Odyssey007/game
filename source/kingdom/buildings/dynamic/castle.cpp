#include "../header/kingdom/buildings/dynamic/castle.h"

Castle::Castle() {
    level = 1; // Will be loaded from the saved data; 
    bounds.left = 10; // Will be loaded from the saved data; 
    bounds.top = 10; // Will be loaded from the saved data;  

    // Setting up castle sprite
    if (!texture.loadFromFile("assets/kingdom/castle.png")) {
        std::cerr << "Error loading castle texture!" << std::endl;
    } else {
        setupRect(); 
    }
}

void Castle::setupRect() {
    sf::Vector2u textureSize = texture.getSize();
    bounds.width = static_cast<float>(textureSize.x * 0.3f);
    bounds.height = static_cast<float>(textureSize.y * 0.27f);
    rect.width = texture.getSize().x; 
    rect.height = texture.getSize().y;

    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
    sprite.setScale(0.3f, 0.27f); 
    sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
    sprite.setPosition(sf::Vector2f(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f));
}

std::string Castle::getName() {
    return "Castle"; 
}

sf::Vector2f Castle::getPosition() {
    return sf::Vector2f {bounds.left, bounds.top}; 
}

void Castle::upgradeCost() { 
    if (level % 5 == 0) {
        calculateCost(2000, 1000, 0); // Gold
        cost[1] = 0; // Food
        calculateCost(1500, 600, 2);  // Wood
        calculateCost(500, 500, 3);   // Stone
    } else {
        calculateCost(2000, 500, 0); // Gold 
        cost[1] = 0; // Food 
        calculateCost(1500, 300, 2); // Wood 
        calculateCost(500, 200, 3); // Stone
    }
}

void Castle::upgrade() {
    level++; 
    upgradeCost(); 
    //- Increment to stats logic for castle goes here once decided on the stats. 
}

sf::Vector2f Castle::bottomMid() {
    return sf::Vector2f (bounds.left + (bounds.width/2), bounds.top + bounds.height + 5); 
}

void Castle::render(sf::RenderWindow& window) {
    sf::RectangleShape drawRect; 
    drawRect.setOutlineColor(sf::Color::Red); 
    drawRect.setOutlineThickness(1.0f); 
    drawRect.setFillColor(sf::Color::Transparent); 
    drawRect.setSize(sf::Vector2f(bounds.width, bounds.height)); 
    drawRect.setPosition(bounds.left, bounds.top);

    window.draw(drawRect); 
    window.draw(sprite); 
}