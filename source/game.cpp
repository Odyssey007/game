#include "../header/game.h"

//preset values into setting up window
Game::Game() : 
    //window setup
    window(nullptr), resolution(sf::VideoMode::getDesktopMode()),
    //entities
    player(std::make_shared<Player>()), slimeNum(1),
    slimes(std::make_shared<std::vector<std::shared_ptr<Slime>>>())
{
    //preliminaries
    currentWindow();
    //entities
    player->initialPosition(); //player
    collisionManager.addEntity(player); 
    for (size_t i = 0; i < slimeNum; i++) { //slimes
        std::shared_ptr<Slime> slime = std::make_shared<Slime>();
        slimes->push_back(slime);
        collisionManager.addEntity(slime);
    }
}

//sets up the window
void Game::currentWindow() {
    window = std::make_unique<sf::RenderWindow>(resolution, "Project-AA", sf::Style::Fullscreen);
    window->setFramerateLimit(120);
}

bool Game::winRunning() const {
    return window->isOpen();
}

void Game::update() {
    handleEvents();
    //update entities
    
    player->update();
    for (auto& slime : *slimes) {
        slime->update((player->getShape()).getPosition(), 100.0f);
    }
    //collision check
    collisionManager.checkCollisions();
    //is game over?
    checkGameEnd();
}

void Game::handleEvents() {
    while(window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) window->close();
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) window->close();
        }
    }
}

void Game::checkGameEnd() {
    //std::cout << player->getHealth() << std::endl;
    if (player->getHealth() == 0) {
        throw std::runtime_error("Game Over\n");
    }
}

void Game::render() {
    window->clear();
    //entities
    for (const auto& slime : *slimes) { //slimes
        slime->render(*window);
    }
    player->render(*window); //player
    window->display();
}