#pragma once
#include "../header/utility.h"
#include "../header/kingdom/buildings/dynamic/dynamicAsset.h"

class Huts : public DynamicAssets {
private: 
public: 
    sf::FloatRect hutRect; 
    std::vector<sf::FloatRect> hutPool; 

    //Constructor
    Huts(); 
    //Base functions 
    virtual void upgrade() override; 
    virtual sf::Vector2f bottomMid() override; 
    virtual void moveBuilding(float x, float y) override; 
    virtual void render(sf::RenderWindow& window) override; 
};