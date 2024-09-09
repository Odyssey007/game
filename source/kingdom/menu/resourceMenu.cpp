#include "../header/kingdom/menu/resourceMenu.h"

ResourceMenu::ResourceMenu(const std::string& name, const sf::Font& font) :
    drop(false)
{
    //Resource rectangle 
    resourceRect.setSize({150, 30});
    resourceRect.setPosition(0, 0); 
    resourceRect.setFillColor(sf::Color(70, 70, 70));

    //Dropdown rectangle 
    dropdownRect.setSize({150, 200}); 
    dropdownRect.setPosition(0, 0); 
    dropdownRect.setFillColor(sf::Color(20, 100, 90));

    //Resource name 
    resourceName.setString(name); 
    resourceName.setFont(font); 
    resourceName.setFillColor(sf::Color::White);
    resourceName.setCharacterSize(20); 
    resourceName.setPosition(0, 0);
    sf::FloatRect textBounds = resourceName.getLocalBounds(); 
    resourceName.setOrigin(textBounds.left+ textBounds.width, 
                          textBounds.top + textBounds.height / 2.0f); 

    //Resource information
    info.setFont(font);
    info.setFillColor(sf::Color::White);
    info.setCharacterSize(17);
    info.setPosition(0, 0);
    sf::FloatRect infoBounds = info.getLocalBounds(); 
    info.setOrigin(infoBounds.left + infoBounds.width / 2.0f, 
                          infoBounds.top + infoBounds.height / 2.0f); 
}

void ResourceMenu::setPosition(sf::Vector2f position) { 
    resourceRect.setPosition(position); 
    sf::FloatRect bounds = resourceRect.getGlobalBounds(); 
    float x = (bounds.width - 5) + bounds.left; 
    float y = (bounds.height/2) + bounds.top; 
    resourceName.setPosition(x, y);

    if(drop) {
        toggleDropdown(); 
    }
}

void ResourceMenu::updateAmount(int newAmount) {
    newAmount = 0; 
}

void ResourceMenu::toggleDropdown() {
    drop = true; 
    information.clear(); 

    sf::FloatRect bounds = resourceRect.getGlobalBounds();
    dropdownRect.setPosition(bounds.left, bounds.top + bounds.height);
    sf::FloatRect dropBounds = dropdownRect.getGlobalBounds(); 
    float a = dropBounds.left + 30; 
    float b = dropBounds.top + 10; 
    info.setPosition(a, b); 

    for(int i = 0; i < 4; i++) {
        info.setPosition(a, b + 30*i); 
        info.setString("Information"); 
        information.emplace_back(info); 
    }
}

void ResourceMenu::render(sf::RenderWindow& window) {
    window.draw(resourceRect); 
    window.draw(resourceName); 
    if(drop) {
        window.draw(dropdownRect); 
        for( auto& info : information) { 
            window.draw(info); 
        }
    }
}