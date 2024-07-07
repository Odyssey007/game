#include "../header/game.h"

//preset values into setting up window
Game::Game() : 
    //window setup
    window(nullptr), resolution(sf::Vector2u(0, 0)),
    //entities
    player(std::make_shared<Player>()), 
    slimes(std::make_shared<std::vector<std::shared_ptr<Slime>>>()),
    staticObstacles(std::make_shared<std::vector<std::shared_ptr<StaticObstacle>>>())
{
    //?temp
    slimeNum = 10; staticObstacleNum = 1; 
    //preliminaries
    currentWindow();
    //entities
    player->initialPosition(sf::Vector2u(650, 500)); //player
    collisionManager.addEntity(player); 
    for (size_t i = 0; i < slimeNum; i++) { //slimes
        std::shared_ptr<Slime> slime = std::make_shared<Slime>();
        slime->initialPosition(resolution);
        slimes->push_back(slime);
        collisionManager.addEntity(slime);
    }
    for (size_t i = 0; i < staticObstacleNum; i++) { //static obstacles
        std::shared_ptr<StaticObstacle> obstacle = std::make_shared<StaticObstacle>();
        staticObstacles->push_back(obstacle);
        collisionManager.addEntity(obstacle);
    }
}

//sets up the window
void Game::currentWindow() {
    //resolution
    sf::VideoMode screen = sf::VideoMode::getDesktopMode();
    resolution.x = screen.width; resolution.y = screen.height;
    //window
    window = std::make_unique<sf::RenderWindow>(screen, "Project-AA", sf::Style::Fullscreen);
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
    for (const auto& obstacle : *staticObstacles) { //static obstacles
        obstacle->render(*window);
    }
    player->render(*window); //player
    window->display();
}