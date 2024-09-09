#include "../header/kingdom/menu/menu.h"

KingdomMenu::KingdomMenu() :
    selectedBuilding(nullptr), building(false), enter(false)
{
    if(!font.loadFromFile("assets/fonts/munro.ttf")) {
        std::cout << "font not working\n";
    }

    buildingManager.addDynamicBuildings(); // Initializing dynamic buildings; 

    //Resource tabs
    resources.emplace_back("Population", font); 
    resources.emplace_back("Gold", font); 
    resources.emplace_back("Food", font); 
    resources.emplace_back("Wood", font); 
    resources.emplace_back("Stone", font); 

    //Add and edit buttons 
    buttons.emplace_back("Add Buildings", font); 
    buttons.emplace_back("Edit Kingdoms", font); 

    //Upgrade buttons for buildings
    buildings.emplace_back("Upgrade", font);
    buildings.emplace_back("Enter", font); 
    for (auto& building : buildings) {
        building.buttonRect.setSize({80, 30}); 
    }
}

void KingdomMenu::handleEvent(sf::RenderWindow& window, sf::Event& event) {
    flag = true;
    mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        handleResourceTabs();
        handleAddEditButtons();
        if (flag) {
            handleBuildingButtons();
        }
    }
}

void KingdomMenu::handleResourceTabs() {
    for (auto& resource : resources) {
        if (resource.resourceRect.getGlobalBounds().contains(mousePos)) {
            flag = false;
            resource.toggleDropdown();
        } else {
            resource.drop = false;
        }
    }
}

void KingdomMenu::handleAddEditButtons() {
    // Logic for Add Buttons in the kingdom.
    if (buttons[0].buttonRect.getGlobalBounds().contains(mousePos)) {
        flag = false;
        buttons[0].addEntity();
    } else {
        bool clicked = false;
        for (unsigned int i = 0; i < buttons[0].addRect.size(); i++) {
            if (buttons[0].addRect[i].getGlobalBounds().contains(mousePos)) {
                flag = false;
                if (buttons[0].addText[i].getString() == "Add Huts") {
                    buildingManager.addHuts();
                    buildingManager.allBuilding(); 
                }

                if (buttons[0].addText[i].getString() == "Add Farms") {
                    buildingManager.addFarms();
                    buildingManager.allBuilding(); 
                }

                if (buttons[0].addText[i].getString() == "Add Animal Farms") {
                    buildingManager.addAnimalFarms();
                    buildingManager.allBuilding(); 
                }

                clicked = true;
                break;
            }
        }
        if (!clicked) {
            buttons[0].showAddMenu = false;
        }
    }

    // Logic for editing the kingdom
    if (buttons[1].buttonRect.getGlobalBounds().contains(mousePos)) {
        flag = false;
        std::cout << "working" << std::endl; 
        buttons[1].editKingdom(mousePos);

        for (auto& dynamicBuildingPair : buildingManager.dynamicBuildings) {
            auto& dynamicBuilding = dynamicBuildingPair.second; 
            sf::Vector2f offset = dynamicBuilding->getPosition() - static_cast<sf::Vector2f>(mousePos);
            
            if (dynamicBuilding->bounds.contains(mousePos)) {
                dynamicBuilding->sprite.setPosition(static_cast<sf::Vector2f>(mousePos) + offset);
            }
        }
    }
}

void KingdomMenu::handleBuildingButtons() {
    for (auto& dynamicBuildingPair : buildingManager.dynamicBuildings) {
        auto& dynamicBuilding = dynamicBuildingPair.second; 
        enter = false;
        
        if (dynamicBuilding->bounds.contains(mousePos)) {
            building = true;
            selectedBuilding = dynamicBuilding.get(); 

            if (dynamicBuilding->getName() == "Castle" || dynamicBuilding->getName() == "Shop") {
                enter = true;
            }
            break;
        } else {
            if (buildings[0].buttonRect.getGlobalBounds().contains(mousePos)) {
                buildings[0].upgrade();
            }

            if (buildings[1].buttonRect.getGlobalBounds().contains(mousePos)) {
                buildings[1].enter();
            }

            building = false;
            enter = false;
            selectedBuilding = nullptr; 
        }
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
            buildings[0].setPosition(center, selectedBuilding->bottomMid() + sf::Vector2f(-(buildings[0].buttonRect.getSize().x + 5), 0));
            buildings[1].setPosition(center, selectedBuilding->bottomMid() + sf::Vector2f(5, 0));
        } else {
            buildings[0].setPosition(center, selectedBuilding->bottomMid() + sf::Vector2f(-buildings[0].buttonRect.getSize().x/2, 0)); 
        }
    }
}

void KingdomMenu::render(sf::RenderWindow& window) {
    buildingManager.renderBuildings(window);

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