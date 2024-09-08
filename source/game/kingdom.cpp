#include "../header/game/kingdom.h"

KingdomState::KingdomState() : 
    resolution(0.0f, 0.0f),
    player(std::make_shared<Player>())
{}

void KingdomState::enter(sf::RenderWindow& window) {
    view = window.getDefaultView();
    resolution = window.getSize(); 
    sf::FloatRect screenBounds = sf::FloatRect(view.getCenter() - view.getSize() / 2.0f, view.getSize());

    player->setInitialPosition(screenBounds); 
}

void KingdomState::handleEvents(sf::RenderWindow& window, sf::Event& event) {
    mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    if (event.type == sf::Event::MouseButtonPressed) {
        menu.handleEvent(window, event); 
    }
}

void KingdomState::update(sf::RenderWindow& window, sf::Event& event) {
    view.setCenter(player->getBounds().left + player->getBounds().width/2.0f, 
                player->getBounds().top + player->getBounds().height/2.0f);
    
    player->update(mousePos); 
    player->applyMovement();
    menu.positionMenu(view.getCenter(), resolution);  
    //buildings.allBuilding();
}

void KingdomState::render(sf::RenderWindow& window) {
    window.setView(view);
    player->render(window);  
    menu.render(window); 
}

void KingdomState::exit() {
    std::cout << "bye" << std::endl; 
}

StateMode KingdomState::getStateType() {
    return KINGDOM; 
}