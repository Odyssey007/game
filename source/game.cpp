#include "../header/game.h"

//preset values into setting up window
Game::Game() : 
    //window setup
    window(nullptr), resolution(sf::Vector2u(0, 0)),
    //entities
    player(std::make_shared<Player>()), 
    slimes(std::make_shared<std::vector<std::shared_ptr<Slime>>>()),
    objects(std::make_shared<std::vector<std::shared_ptr<Object>>>()),
    quadTree(sf::FloatRect(0, 0, 1920, 1080), 3)
{
    //?temp
    slimeNum = 10; objectNum = 1; 
    //preliminaries
    currentWindow();
    //entities
    player->setInitialPosition(sf::Vector2u(650, 500)); //player
    collisionManager.addEntity(player); 
    slimePool.getSlimes(resolution);
    for(auto& slime: slimePool.activeSlimes) {
        collisionManager.addEntity(slime); 
    }

    for (size_t i = 0; i < objectNum; i++) { //static obstacles
        std::shared_ptr<Object> object = std::make_shared<Object>();
        objects->push_back(object);
        collisionManager.addObject(object);
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
    view = window->getDefaultView();
}

bool Game::winRunning() const {
    return window->isOpen();
}

void Game::update() {
    handleEvents();
    //update entities
    player->update();
    view.setCenter(player->getShape().getGlobalBounds().left, player->getShape().getGlobalBounds().top);

    if(slimePool.activeSlimes.size() == 0) {
        slimePool.getSlimes(resolution); 
    }

    for (auto& slime : slimePool.activeSlimes) {
        slime->update((player->getShape()).getPosition(), 100.0f);
    }


    //collision check
    collisionManager.checkCollisions();
    player->applyMovement();

    for (auto& slime : slimePool.activeSlimes) {
        slime->applyMovement();
    }

    quadTree.clear(); 
    quadTree.insertObject(player->getShape().getGlobalBounds()); 
    for(auto& slime : slimePool.activeSlimes) {
        quadTree.insertObject(slime->getShape().getGlobalBounds()); 
    }

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
    // if (player->getHealth() == 0) {
    //     throw std::runtime_error("Game Over\n");
    // }
}

void Game::render() {
    window->setView(view);
    window->clear();
    //entities
    for (const auto& obstacle : *objects) { //static obstacles
        obstacle->render(*window);
    }

    // for (const auto& slime : *slimes) { //slimes
    //     slime->render(*window);
    // }

    for(const auto& slime: slimePool.activeSlimes) {
        slime->render(*window);
    }

    player->render(*window); //player
    quadTree.draw(*window); 
    window->display();
}