#pragma once
#include "../header/utility.h"
#include "../header/kingdom/buildings/dynamic/dynamicAsset.h"

class Castle : public DynamicAssets {
private:
public: 
    sf::FloatRect castleRect; 

    //Constructor; 
    Castle(); 
    //Base functions 
    virtual void upgrade() override; 
    virtual sf::Vector2f bottomMid() override; 
    virtual void moveBuilding(float x, float y) override; 
    virtual void render(sf::RenderWindow& window) override; 
};