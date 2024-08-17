#include "../header/game/kingdom.h"

KingdomState::KingdomState() : 
    resolution(0.0f, 0.0f),
    player(std::make_shared<Player>())
{}

void KingdomState::enter(sf::RenderWindow& window) {
    view = window.getDefaultView();
    resolution - window.getSize(); 

    player->setInitialPosition(sf::FloatRect(0.0f, 0.0f, 0.0f, 0.0f)); 

    dynamicAsset.kingCastle();
    dynamicAsset.huts(); 
    dynamicAsset.multipurpose(); 
    dynamicAsset.scienceTech(); 
    dynamicAsset.blacksmithWeapon(); 
    dynamicAsset.farms();
    dynamicAsset.paths(); 
    dynamicAsset.animalFarms();

    staticAsset.kingdomWall(); 
    staticAsset.trees();
    staticAsset.civilians(); 
}

void KingdomState::update(sf::RenderWindow& window, sf::Event& event) {
    view.setCenter(player->getBounds().left + player->getBounds().width/2.0f, 
                player->getBounds().top + player->getBounds().height/2.0f);
    
    mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    player->update(mousePos); 
    player->applyMovement(); 
}

void KingdomState::handleEvents(sf::RenderWindow& window, sf::Event& event) {
    while(window.pollEvent(event)) {
        if(event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) window.close();
        }
    }
}

void KingdomState::render(sf::RenderWindow& window) {
    window.setView(view);
    player->render(window); 
    dynamicAsset.render(window); 
    staticAsset.render(window); 
}

void KingdomState::exit() {
    std::cout << "bye" << std::endl; 
}

StateMode KingdomState::getStateType() {
    return KINGDOM; 
}