#include "../header/kingdom/buildings/dynamic/storage.h"

Storage::Storage() {
    level = 1; // Will be loaded from the saved data
    bounds.left = 1750; // Will be loaded from the saved data
    bounds.top = 10;   // Will be loaded from the saved data

    // Load the storage texture
    if (!texture.loadFromFile("assets/kingdom/storage.png")) {
        std::cerr << "Error loading huts texture!" << std::endl;
    } else {
        setupRect(); 
    }
}

void Storage::setupRect() {
    sf::Vector2u textureSize = texture.getSize();
    bounds.width = static_cast<float>(textureSize.x * 1.32f);
    bounds.height = static_cast<float>(textureSize.y * 1.2f);
    rect.width = texture.getSize().x; 
    rect.height = texture.getSize().y;

    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
    sprite.setScale(1.32f, 1.2f); 
    sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
    sprite.setPosition(sf::Vector2f(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f));
}

std::string Storage::getName() {
    return "Storage";
}

sf::Vector2f Storage::getPosition() {
    return sf::Vector2f {bounds.left, bounds.top}; 
}

void Storage::upgrade() {
    level++; 
    upgradeCost();
    //- Upgrade logic for castle goes here. 
}

void Storage::upgradeCost() {
    if (level % 5 == 0) {
        calculateCost(300, 250, 0); // Gold 
        cost[1] = 0; // Food 
        calculateCost(1000, 400, 2); // Wood 
        calculateCost(500, 400, 3); // Stone
    } else {
        calculateCost(300, 100, 0); // Gold 
        cost[1] = 0; // Food 
        calculateCost(1000, 200, 2); // Wood 
        calculateCost(500, 200, 3); // Stone
    }
}

sf::Vector2f Storage::bottomMid() {
    return sf::Vector2f (bounds.left + (bounds.width/2), bounds.top + bounds.height + 5); 
}

void Storage::render(sf::RenderWindow& window) {
    sf::RectangleShape drawRect; 
    drawRect.setOutlineColor(sf::Color::Red); 
    drawRect.setOutlineThickness(1.0f); 
    drawRect.setFillColor(sf::Color::Transparent); 
    drawRect.setSize(sf::Vector2f(bounds.width, bounds.height)); 
    drawRect.setPosition(bounds.left, bounds.top);

    window.draw(drawRect); 
    window.draw(sprite); 
}