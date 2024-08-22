#include "../header/game/kingdom.h"

KingdomState::KingdomState() : 
    resolution(0.0f, 0.0f),
    player(std::make_shared<Player>())
{}

void KingdomState::enter(sf::RenderWindow& window) {
    view = window.getDefaultView();
    resolution = window.getSize(); 

    player->setInitialPosition(sf::FloatRect(0.0f, 0.0f, 0.0f, 0.0f)); 

    // dynamicAsset.kingCastle();
    // dynamicAsset.huts(); 
    // dynamicAsset.multipurpose(); 
    // dynamicAsset.scienceTech(); 
    // dynamicAsset.blacksmithWeapon(); 
    // dynamicAsset.farms();
    // dynamicAsset.animalFarms();

     staticAsset.kingdomWall(); 
    // staticAsset.trees();
    // staticAsset.civilians(); 
}

void KingdomState::handleEvents(sf::RenderWindow& window, sf::Event& event) {
    mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    if (event.type == sf::Event::MouseButtonPressed) {
        // if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        //     if (castle.castleRect.contains(mousePos)) {
        //         castle.moveBuilding(mousePos.x, mousePos.y); 
        //     }
        // }
        menu.handleEvent(window, event); 
    }
}

void KingdomState::update(sf::RenderWindow& window, sf::Event& event) {
    view.setCenter(player->getBounds().left + player->getBounds().width/2.0f, 
                player->getBounds().top + player->getBounds().height/2.0f);
    
    player->update(mousePos); 
    player->applyMovement();
    menu.positionMenu(view.getCenter(), resolution);  
}

void KingdomState::render(sf::RenderWindow& window) {
    window.setView(view);
    player->render(window); 
    //dynamicAsset.render(window); 
    staticAsset.render(window);
    castle.render(window);  
    menu.render(window); 
}

void KingdomState::exit() {
    std::cout << "bye" << std::endl; 
}

StateMode KingdomState::getStateType() {
    return KINGDOM; 
}