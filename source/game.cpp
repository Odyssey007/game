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
    //this->window->setVerticalSyncEnabled(true); 
    //this->window->setFramerateLimit(60);
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

void Game::checkCollision() {
    if (player.hitBoxC.collisionCheckC(s1.hitBoxC.dot)) {
        player.handleCollision(s1);
    }
}

//update game
void Game::update() {
    this->handleEvents(); //handle all events
    player.playerMovement();

    s1.action(player.player_sprite.getPosition(), 100.0f);

    checkCollision();
}

//render objects onto the screen || display frame on window
void Game::render() {
    this->window->clear();

    this->window->draw(s1.enemySprite);
    //this->window->draw(s1.hitBox.body);
    this->window->draw(s1.hitBoxC.dot);



    this->window->draw(player.player_sprite);
    //this->window->draw(player.hitBox.body);
    this->window->draw(player.hitBoxC.dot);


    this->window->display();
}