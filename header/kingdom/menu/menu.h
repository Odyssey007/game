#pragma once
#include "../header/utility.h"
#include "../header/kingdom/menu/buttonMenu.h"
#include "../header/kingdom/menu/resourceMenu.h"
#include "../header/kingdom/buildings/dynamic/castle.h"
#include "../header/kingdom/buildings/buildingManager.h"

class KingdomMenu {
private: 
    sf::RectangleShape background; 
    sf::Vector2f mousePos; 
    sf::Vector2f worldPos;
    sf::Text text[5]; // population, gold, food, wood, metals, add, edit
    sf::Font font; 
    bool flag; 

    DynamicAssets* selectedBuilding;
    BuildingManager buildingManager; 
public: 
    //Game controls
    std::vector<ResourceMenu> resources; 
    std::vector<ButtonMenu> buttons; 
    //Building controls 
    std::vector<ButtonMenu> buildings;
    bool building; 
    bool enter; 

    //Constructor
    KingdomMenu(); 
    //Function
    void render(sf::RenderWindow& window); 
    void positionMenu(sf::Vector2f center, sf::Vector2u resolution); 
    void handleEvent(sf::RenderWindow& window, sf::Event& event); 
    void handleResourceTabs();
    void handleAddEditButtons();
    void handleBuildingButtons();
};

class CastleMenu {

};

class ShopMenu {

}; 