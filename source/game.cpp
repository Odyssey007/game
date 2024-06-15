#include "../header/game.h"

//preset values into setting up window
Game::Game() {
    //initalize varaibels for window
    this->window = nullptr;
    this->window->setFramerateLimit(60);
    this->resolution = sf::VideoMode(1920, 1080);
    this->curWindow();
}

//sets up the window
void Game::curWindow() {
    //this->resolution.getDesktopMode(); ?? not sure 
    this->window = new sf::RenderWindow(resolution, "Project-AA");
}

//check if window is open
bool Game::winRunning() const {
    return this->window->isOpen();
}

//event loop
void Game::update() {
    while(this->window->pollEvent(this->event)) {
        if (this->event.type == sf::Event::Closed) {
            this->window->close();
        }
    }
}

//render objects onto the screen || display frame on window
void Game::render() {
    this->window->clear();
    this->window->display();
}

//erases the current window
Game::~Game() {
    delete this->window;
}