#pragma once
#include "../header/utility.h"
#include "../header/kingdom/buildings/dynamic/castle.h"

class ButtonMenu {
private: 
    sf::Text buttonName; 
    sf::RectangleShape addMenu; 
public: 
    std::vector<sf::Text> addText; 
    std::vector<sf::RectangleShape> addRect; 
    bool showAddMenu; 
    sf::Vector2f center; 
    sf::RectangleShape buttonRect; 

    //Constructor 
    ButtonMenu(const std::string& name, const sf::Font& font);

    //Function
    void render(sf::RenderWindow& window); 
    void setPosition(sf::Vector2f center, sf::Vector2f position); 
    void addEntity(); 
    void editKingdom(sf::Vector2f mousePos); 
    void upgrade(); 
    void enter(); 
}; 