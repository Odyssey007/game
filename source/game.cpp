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
    //this->window->setFramerateLimit(144);
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
            //key handling
            case sf::Event::KeyPressed:
                if(this->event.key.code == sf::Keyboard::Escape) {
                    this->window->close();
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
    player.battleMovement(deltaTime);
    player.battleMovement_animation();

    slime.movement(player.player_sprite.getPosition(), deltaTime);
}

//render objects onto the screen || display frame on window
void Game::render() {
    this->window->clear();
    this->window->draw(slime.slime_sprite);
    this->window->draw(player.player_sprite);
    this->window->display();
}