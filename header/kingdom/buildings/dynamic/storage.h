#pragma once
#include "../header/utility.h"
#include "../header/kingdom/buildings/dynamic/dynamicAsset.h"

class Storage : public DynamicAssets {
private:
    sf::IntRect rect; 
public:  
    //Constructor; 
    Storage(); 

    //Getters
    virtual std::string getName() override;
    virtual sf::Vector2f getPosition() override;

    //Base functions 
    virtual void upgrade() override; 
    virtual void setupRect() override; 
    virtual void upgradeCost() override; 
    virtual sf::Vector2f bottomMid() override; 
    virtual void render(sf::RenderWindow& window) override; 

    //Functions
};