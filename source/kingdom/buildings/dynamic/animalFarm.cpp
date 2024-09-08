#include "../header/kingdom/buildings/dynamic/animalFarm.h"

AnimalFarms::AnimalFarms() {
    level = 1; // Will be loaded from the saved data
    //? need to change from huts
    bounds.left = 350; // Will be loaded from the saved data
    bounds.top = 500;   // Will be loaded from the saved data

    // Load the hut texture
    if (!texture.loadFromFile("assets/kingdom/huts.png")) {
        std::cerr << "Error loading huts texture!" << std::endl;
    } else {
        setupRect(); 
    }
}

void AnimalFarms::setupRect() {
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


std::string AnimalFarms::getName() {
    return "AnimalFarm"; 
}

sf::Vector2f AnimalFarms::getPosition() {
    return sf::Vector2f {bounds.left, bounds.top}; 
}

void AnimalFarms::upgrade() {
    level++; 
    upgradeCost();
    //- Upgrade logic for castle goes here. 
}

//? need to change
void AnimalFarms::upgradeCost() {
    if (level % 5 == 0) {
        calculateCost(250, 200, 0); // Gold 
        calculateCost(500, 400, 1); // Food 
        calculateCost(500, 400, 2); // Wood 
        cost[3] = 0; // Stone
    } else {
        calculateCost(250, 100, 0); // Gold 
        calculateCost(500, 200, 1); // Food 
        calculateCost(500, 200, 2); // Wood 
        cost[3] = 0; // Stone
    }
}

sf::Vector2f AnimalFarms::bottomMid() {
    return sf::Vector2f (bounds.left + (bounds.width/2), bounds.top + bounds.height + 5); 
}

void AnimalFarms::render(sf::RenderWindow& window) {
    sf::RectangleShape drawRect; 
    drawRect.setOutlineColor(sf::Color::Red); 
    drawRect.setOutlineThickness(1.0f); 
    drawRect.setFillColor(sf::Color::Transparent); 
    drawRect.setSize(sf::Vector2f(bounds.width, bounds.height)); 
    drawRect.setPosition(bounds.left, bounds.top);

    window.draw(drawRect); 
    window.draw(sprite); 
}