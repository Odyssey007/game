#include "../header/kingdom/menu/buttonMenu.h"

ButtonMenu::ButtonMenu(const std::string& name, const sf::Font& font) :
    showAddMenu(false), center(0, 0)
{
    //Button rectangle
    buttonRect.setSize({150, 30}); 
    buttonRect.setPosition(0, 0); 
    buttonRect.setFillColor(sf::Color(70, 70, 70));

    //Background for adding menu
    addMenu.setSize({400, 300});
    addMenu.setPosition(0, 0); 
    addMenu.setFillColor(sf::Color(70, 70, 70)); 
    sf::FloatRect rectA = addMenu.getGlobalBounds(); 
    addMenu.setOrigin(rectA.width/2, rectA.height/2);

    //options for adding buildings
    for (int i = 0; i < 3; i++) {
        sf::RectangleShape rect;
        rect.setSize({300, 30});
        rect.setPosition(0, 0); 
        rect.setFillColor(sf::Color::White);
        sf::FloatRect smallRect = rect.getGlobalBounds(); 
        rect.setOrigin(smallRect.width/2, smallRect.height/2);
        addRect.emplace_back(rect); 
    }

    //Button name
    buttonName.setString(name); 
    buttonName.setFont(font); 
    buttonName.setFillColor(sf::Color::White); 
    buttonName.setCharacterSize(20); 
    buttonName.setPosition(0, 0);
    sf::FloatRect bounds = buttonName.getLocalBounds(); 
    buttonName.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f); 

    //Name for adding buildings
    sf::Text text1;
    sf::Text text2;
    sf::Text text3;

    text1.setString("Add Huts");
    text2.setString("Add Farms");
    text3.setString("Add Animal Farms");

    addText.emplace_back(text1); 
    addText.emplace_back(text2); 
    addText.emplace_back(text3); 

    for(int i = 0; i < 3; i++) {
        addText[i].setFont(font); 
        addText[i].setFillColor(sf::Color::Black);
        addText[i].setCharacterSize(20);
        addText[i].setPosition(0, 0);
        sf::FloatRect rect = addText[i].getLocalBounds(); 
        addText[i].setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
    }
}

void ButtonMenu::setPosition(sf::Vector2f center, sf::Vector2f position) {
    this->center = center; 
    buttonRect.setPosition(position);
    sf::FloatRect bounds = buttonRect.getGlobalBounds(); 
    float x = (bounds.width/2) + bounds.left; 
    float y = (bounds.height/2) + bounds.top; 
    buttonName.setPosition(x, y);

    if (showAddMenu) {
        addEntity(); 
    }
}

void ButtonMenu::addEntity() {
    showAddMenu = true; 
    addMenu.setPosition(center); 
    sf::FloatRect bounds = addMenu.getGlobalBounds(); 
    float x = center.x; 
    float y = bounds.top + 100; 

    for (unsigned int i = 0; i < addRect.size(); i++) {
        addRect[i].setPosition(x, y + 40 * i);

        sf::FloatRect rect = addRect[i].getGlobalBounds(); 
        float a = (rect.width/2) + rect.left; 
        float b = (rect.height/2) + rect.top; 
        addText[i].setPosition(a, b); 
    }
}

void ButtonMenu::editKingdom(sf::Vector2f mousePos) {
    bool edit = true; 

    while (edit) {
        if (castle.castleRect.contains(mousePos)) {
            castle.moveBuilding(mousePos.x, mousePos.y); 
            edit = false; 
        }
    }
}

void ButtonMenu::upgrade() {
    std::cout << "Can upgrade" << std::endl;
}

void ButtonMenu::enter() {
    std::cout << "Can enter" << std::endl;
}

void ButtonMenu::render(sf::RenderWindow& window) {
    window.draw(buttonRect); 
    window.draw(buttonName); 

    if (showAddMenu) {
        window.draw(addMenu); 
        for (unsigned int i = 0; i < addRect.size(); i++) {
            window.draw(addRect[i]);
            window.draw(addText[i]); 
        }
    }
}