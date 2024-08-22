#pragma once
#include "../header/utility.h"

class DynamicAssets {
public:
    //Constructor and destructor 
    DynamicAssets() = default; 
    ~DynamicAssets() = default; 

    //Functions for buildings 
    virtual void upgrade() = 0; 
    virtual sf::Vector2f bottomMid() = 0; 
    virtual void moveBuilding(float x, float y) = 0; 
    virtual void render(sf::RenderWindow& window) = 0; 
};