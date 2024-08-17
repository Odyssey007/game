#include "../header/kingdom/staticAsset.h"

StaticAsset::StaticAsset() :
    civilianPoolSize(20)
{}

void StaticAsset::kingdomWall() { 
    sf::FloatRect northWall;
    sf::FloatRect southWall;
    sf::FloatRect eastWall;
    sf::FloatRect westWall;

    northWall.left = 0.0f;
    northWall.top = 0.0f;
    northWall.width = 2000.0f; 
    northWall.height = -10.0f; 

    eastWall.left = 2000.0f;
    eastWall.top = -10.0f;
    eastWall.width = 10.0f; 
    eastWall.height = 2020.0f; 

    southWall.left = 0.0f;
    southWall.top = 2000.0f;
    southWall.width = 2000.0f; 
    southWall.height = 10.0f; 

    westWall.left = 0.0f;
    westWall.top = -10.0f;
    westWall.width = -10.0f; 
    westWall.height = 2020.0f; 

    staticObject.push_back(northWall); 
    staticObject.push_back(southWall); 
    staticObject.push_back(eastWall); 
    staticObject.push_back(westWall); 
}

void StaticAsset::riverFlow() {
    sf::FloatRect river;
    staticObject.push_back(river); 
}

void StaticAsset::trees() {
    sf::FloatRect tree;

    tree.left = 900.0f;
    tree.top = 1500.0f; 
    tree.width = 70.0f; 
    tree.height = 350.0f; 

    staticObject.push_back(tree); 
}

void StaticAsset::civilians() {
    sf::FloatRect civilian; 

    civilian.left = 300.0f; 
    civilian.top = 650.0f; 
    civilian.width = 32.0f;
    civilian.height = 50.0f;

    for(unsigned int i = 0; i < civilianPoolSize; i++) {
        civilianPool.push_back(civilian); 
    }
    
    //? Need to figure out how where to add civilian
}

void StaticAsset::backForest() {
    sf::FloatRect forest;
    staticObject.push_back(forest);  
}

void StaticAsset::shops() {
    sf::FloatRect shop;
    staticObject.push_back(shop); 
}

void StaticAsset::render(sf::RenderWindow& window) {
    for(auto& rect : staticObject) {
        sf::RectangleShape drawRect; 
        drawRect.setOutlineColor(sf::Color::Red); 
        drawRect.setOutlineThickness(1.0f); 
        drawRect.setFillColor(sf::Color::Transparent); 
        drawRect.setSize(sf::Vector2f(rect.width, rect.height)); 
        drawRect.setPosition(rect.left, rect.top);
        window.draw(drawRect); 
    }
}