#pragma once
#include "../header/utility.h"

class ResourceMenu {
private: 
public:  
    sf::Text info; 
    sf::Text resourceName;
    sf::Text resourceAmount; 
    sf::RectangleShape resourceRect;
    sf::RectangleShape dropdownRect;  
    std::vector<sf::Text> information; 

    bool drop; 
    //Constructor
    ResourceMenu(const std::string& name, const sf::Font& font); 

    //Function
    void toggleDropdown();
    void updateAmount(int newAmount); 
    void render(sf::RenderWindow& window); 
    void setPosition(sf::Vector2f position);  
}; 