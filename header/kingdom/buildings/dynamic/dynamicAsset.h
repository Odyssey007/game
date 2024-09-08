#pragma once
#include "../header/utility.h"

class DynamicAssets {
protected: 
    sf::Texture texture; 
    int level; 
    std::vector<int> cost; //1-gold, 2-food, 3-wood, 4-metals/iron/stone
public:
    sf::Sprite sprite; 
    std::string name; 
    sf::FloatRect bounds; 
    //Constructor and destructor 
    DynamicAssets();
    ~DynamicAssets() = default;

    void calculateCost(unsigned int baseCost,unsigned int increment,unsigned int resourceIndex);

    //Getters
    virtual std::string getName() = 0;
    virtual sf::Vector2f getPosition() = 0;

    //Functions for buildings 
    //virtual void displayInfo() = 0; 
    virtual void upgrade() = 0; 
    virtual void setupRect() = 0;
    virtual void upgradeCost() = 0; 
    virtual sf::Vector2f bottomMid() = 0; 
    virtual void render(sf::RenderWindow& window) = 0; 
};