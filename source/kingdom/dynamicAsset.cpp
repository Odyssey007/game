#include "../header/kingdom/dynamicAsset.h"

DynamicAsset::DynamicAsset() :
    hutPoolSize(10), farmPoolSize(8), animalFarmSize(4)
{}

void DynamicAsset::kingCastle() {
    sf::FloatRect castle; 

    castle.left = 70.0f; 
    castle.top = 50.0f;
    castle.width = 500.0f;
    castle.height = 500.0f;

    dynamicObject.push_back(castle); 
}

void DynamicAsset::huts() {
    sf::FloatRect hut; 

    hut.left = 600.0f; 
    hut.top = 10.0f; 
    hut.width = 100.0f;
    hut.height = 100.0f;  
    
    for(unsigned int i = 0; i < hutPoolSize; i++) {
        hutPool.push_back(hut); 
    }
    //-needs to be added to dynamicObject
}

void DynamicAsset::multipurpose() {
    sf::FloatRect storage; 

    storage.left = 10.0f; 
    storage.top = 600.0f; 
    storage.width = 200.0f;
    storage.height = 200.0f; 

    for(int i = 0; i < 4; i++) {
        dynamicObject.push_back(storage); 
    }
}

void DynamicAsset::scienceTech() {
    sf::FloatRect science; 

    science.left = 890.0f; 
    science.top = 890.0f;
    science.width = 300.0f; 
    science.height = 300.0f; 

    dynamicObject.push_back(science); 
}

void DynamicAsset::blacksmithWeapon() {
    sf::FloatRect blacksmith; 

    blacksmith.left = 890.0f; 
    blacksmith.top = 10.0f;
    blacksmith.width = 200.0f; 
    blacksmith.height = 200.0f; 

    dynamicObject.push_back(blacksmith);  
}

void DynamicAsset::farms() {
    sf::FloatRect farm; 

    farm.left = 1500.0f; 
    farm.top = 10.0f;
    farm.width = 70.0f; 
    farm.height = 150.0f; 

    for(unsigned int i = 0; i < farmPoolSize; i++) {
        farmPool.push_back(farm); 
    }
    dynamicObject.push_back(farm);  
}

void DynamicAsset::paths() {
    sf::FloatRect path;

    path.left = 10.0f; 
    path.top = 1500.0f; 
    path.width = 50.0f;
    path.height = 50.0f; 

    dynamicObject.push_back(path); 
}

void DynamicAsset::animalFarms() {
    sf::FloatRect animalFarm;

    animalFarm.left = 1000.0f; 
    animalFarm.top = 500.0f; 
    animalFarm.width = 200.0f; 
    animalFarm.height = 200.0f; 

    for(unsigned int i = 0; i < animalFarmSize; i++) {
        animalFarmPool.push_back(animalFarm); 
    }
    dynamicObject.push_back(animalFarm);  
}

void DynamicAsset::render(sf::RenderWindow& window) {
    for(auto& rect : dynamicObject) {
        sf::RectangleShape drawRect; 
        drawRect.setOutlineColor(sf::Color::Red); 
        drawRect.setOutlineThickness(1.0f); 
        drawRect.setFillColor(sf::Color::Transparent); 
        drawRect.setSize(sf::Vector2f(rect.width, rect.height)); 
        drawRect.setPosition(rect.left, rect.top);
        window.draw(drawRect); 
    }
}