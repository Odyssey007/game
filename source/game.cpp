#include "../header/game.h"


//preset values into setting up window
Game::Game() {
    //initialize variables for window
    this->window = nullptr;
    this->resolution = sf::VideoMode::getDesktopMode();
    this->currentWindow();
}

//sets up the window
void Game::currentWindow() {
    //this->resolution.getDesktopMode(); ?? not sure 
    this->window = std::make_unique <sf::RenderWindow> (this->resolution, "Project-AA", sf::Style::Fullscreen);
    this->window->setVerticalSyncEnabled(true); 
    this->window->setFramerateLimit(60);
}

//check if window is open
bool Game::winRunning() const {
    return this->window->isOpen();
}

//event loop
void Game::handleEvents() {
    while(this->window->pollEvent(this->event)) {
        switch(this->event.type) {
            case sf::Event::Closed:
                this->window->close(); 
                break;
            //logic for key handling
            case sf::Event::KeyPressed:
                if(this->event.key.code == sf::Keyboard::Escape) {
                    this->window->close();
                }
                break; 
            case sf::Event::MouseButtonPressed:
                if(event.mouseButton.button == sf::Mouse::Right) {
                    player.mousePosition = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
                    player.movement(player.mousePosition);
                }
                break;
            default:
                break;
        }
        //handle more events if needed. 
    }
}

//update game
void Game::update(float deltaTime) {
    this->handleEvents(); //handle all events
    
    if (player.isMoving) {
        sf::Vector2f currentPosition = player.player_sprite.getPosition();
        sf::Vector2f direction = player.mousePosition - currentPosition; 
        float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
        
        if(distance > 0) {
            direction /= distance; 
            sf::Vector2f movement = direction * player.moveSpeed * deltaTime; 

            if(player.length(movement) > distance) {
                player.player_sprite.setPosition(player.mousePosition);
                player.isMoving = false; 
            }
            else {
                player.player_sprite.move(movement); 
            }
        }
        else {
            player.isMoving = false; 
        }
    }

}

//render objects onto the screen || display frame on window
void Game::render() {
    this->window->clear();
    this->window->draw(player.player_sprite);
    this->window->display();
}
