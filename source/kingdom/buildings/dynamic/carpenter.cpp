#include "../header/kingdom/buildings/dynamic/carpenter.h"

Carpenter::Carpenter() {
    level = 1; // Will be loaded from the saved data
    bounds.left = 1750; // Will be loaded from the saved data
    bounds.top = 115;   // Will be loaded from the saved data

    // Load the hut texture
    if (!texture.loadFromFile("assets/kingdom/carpenter.png")) {
        std::cerr << "Error loading huts texture!" << std::endl;
    } else {
        setupRect(); 
    }
}

void Carpenter::setupRect() {
    sf::Vector2u textureSize = texture.getSize();
    bounds.width = static_cast<float>(textureSize.x);
    bounds.height = static_cast<float>(textureSize.y);
    rect.width = texture.getSize().x; 
    rect.height = texture.getSize().y;

    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
    sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
    sprite.setPosition(sf::Vector2f(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f));
}


std::string Carpenter::getName() {
    return "Carpenter"; 
}

sf::Vector2f Carpenter::getPosition() {
    return sf::Vector2f {bounds.left, bounds.top}; 
}

void Carpenter::upgrade() {
    level++; 
    upgradeCost();
    //- Upgrade logic for castle goes here. 
}

void Carpenter::upgradeCost() {
    if (level % 5 == 0) {
        calculateCost(300, 250, 0); // Gold 
        cost[1] = 0; // Food 
        calculateCost(1500, 400, 2); // Wood 
        calculateCost(250, 400, 3); // Stone
    } else {
        calculateCost(300, 100, 0); // Gold 
        cost[1] = 0; // Food 
        calculateCost(1500, 200, 2); // Wood 
        calculateCost(250, 200, 3); // Stone
    }
}

sf::Vector2f Carpenter::bottomMid() {
    return sf::Vector2f (bounds.left + (bounds.width/2), bounds.top + bounds.height + 5); 
}

void Carpenter::render(sf::RenderWindow& window) {
    sf::RectangleShape drawRect; 
    drawRect.setOutlineColor(sf::Color::Red); 
    drawRect.setOutlineThickness(1.0f); 
    drawRect.setFillColor(sf::Color::Transparent); 
    drawRect.setSize(sf::Vector2f(bounds.width, bounds.height)); 
    drawRect.setPosition(bounds.left, bounds.top);

    window.draw(drawRect); 
    window.draw(sprite); 
}