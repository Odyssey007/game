#include "../header/kingdom/menu/menu.h"

KingdomMenu::KingdomMenu() :
    building(false), enter(false)
{
    if(!font.loadFromFile("assets/fonts/munro.ttf")) {
        std::cout << "font not working\n";
    }

    //Resource tabs
    resources.emplace_back("Population", font); 
    resources.emplace_back("Gold", font); 
    resources.emplace_back("Food", font); 
    resources.emplace_back("Wood", font); 
    resources.emplace_back("Metals", font); 

    //Add and edit buttons 
    buttons.emplace_back("Add Buildings", font); 
    buttons.emplace_back("Edit Kingdoms", font); 

    //Upgrade buttons for buildings
    buildings.emplace_back("Upgrade", font);
    buildings.emplace_back("Enter", font); 
}

void KingdomMenu::handleEvent(sf::RenderWindow& window, sf::Event& event) {
    mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        handleResourceTabs();
        handleAddEditButtons();
        handleBuildingButtons();
    }
}

void KingdomMenu::handleResourceTabs() {
    for (auto& resource : resources) {
        if (resource.resourceRect.getGlobalBounds().contains(mousePos)) {
            resource.toggleDropdown();
        } else {
            resource.drop = false;
        }
    }
}

void KingdomMenu::handleAddEditButtons() {
    if (buttons[0].buttonRect.getGlobalBounds().contains(mousePos)) {
        buttons[0].addEntity();
    } else {
        bool clicked = false;
        for (unsigned int i = 0; i < buttons[0].addRect.size(); i++) {
            if (buttons[0].addRect[i].getGlobalBounds().contains(mousePos)) {
                //? Logic for actual button will be added alter
                clicked = true;
                break;
            }
        }
        if (!clicked) {
            buttons[0].showAddMenu = false;
        }
    }

    if (buttons[1].buttonRect.getGlobalBounds().contains(mousePos)) {
        buttons[1].editKingdom(mousePos);
    }
}

void KingdomMenu::handleBuildingButtons() {
    if (castle.castleRect.contains(mousePos)) {
        building = true;
        enter = true;
    } else {
        if (buildings[0].buttonRect.getGlobalBounds().contains(mousePos)) {
            buildings[0].upgrade();
        }

        if (buildings[1].buttonRect.getGlobalBounds().contains(mousePos)) {
            buildings[1].enter();
        }

        building = false;
        enter = false;
    }
}


void KingdomMenu::positionMenu(sf::Vector2f center, sf::Vector2u resolution) {
    const float resourceSpacing = 165.0f;
    const float buttonSpacing = 43.0f;
    const float buttonYOffset = 150.0f;
    sf::Vector2f topLeft(center.x - resolution.x / 2, center.y - resolution.y / 2);

    // Positioning resource tabs
    for (size_t i = 0; i < resources.size(); ++i) {
        resources[i].setPosition(topLeft + sf::Vector2f(20 + resourceSpacing * i, 10));
    }

    // Positioning add and edit buttons
    sf::Vector2f buttonBasePos(topLeft + sf::Vector2f(20, resolution.y - buttonYOffset));
    for (size_t i = 0; i < buttons.size(); ++i) {
        buttons[i].setPosition(center, buttonBasePos + sf::Vector2f(0, buttonSpacing * i));
    }

    //Positioning upgrade buttons on buildings
    if (building) {
        if (enter) {
            // Positioning when both 'Upgrade' and 'Enter' buttons are active
            buildings[0].setPosition(center, castle.bottomMid() + sf::Vector2f(-155, 0));
            buildings[1].setPosition(center, castle.bottomMid() + sf::Vector2f(5, 0));
        } else {
            // Positioning when only the 'Upgrade' button is active
            buildings[0].setPosition(center, castle.bottomMid() + sf::Vector2f(-75, 0));
        }
    }
}

void KingdomMenu::render(sf::RenderWindow& window) {
    for (auto& resource : resources) {
        resource.render(window); 
    }

    for (auto& button : buttons) {
        button.render(window); 
        //std::cout << "working " << std::endl;
    }

    if (building) {
        buildings[0].render(window); 
        if (enter) {
            buildings[1].render(window);
        }
    }
}