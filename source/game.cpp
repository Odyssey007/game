#include "../header/game.h"

//preset values into setting up window
Game::Game() : 
    //window setup
    window(nullptr), resolution(sf::Vector2u(0, 0)),
    //entities
    player(std::make_shared<Player>()), 
    enemyPool(EnemyType::SLIME, 100), currentWave(1), waveTimer(sf::seconds(10)),
    objects(std::make_shared<std::vector<std::shared_ptr<Object>>>())
{
    //?temp
    objectNum = 1; 
    //preliminaries
    currentWindow();
    //entities
    player->setInitialPosition(sf::Vector2u(650, 500)); //player
    collisionManager.addEntity(player); 
    enemyPool.currentEnemies(currentWave, resolution, collisionManager);

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
    view.setCenter(player->getShape().getGlobalBounds().left, 
                   player->getShape().getGlobalBounds().top);
    //update entities
    player->update();
    enemyPool.update(player->getShape().getPosition());
    //collision check
    collisionManager.update();
    player->applyMovement();
    enemyPool.applyMovement();
    //
    checkWave();
    //
    checkGameEnd();
}

void Game::checkWave() {
    std::cout << waveClock.getElapsedTime().asSeconds() << std::endl;
    if (enemyPool.allDead() || waveClock.getElapsedTime() >= waveTimer) {
        currentWave++;
        enemyPool.resetEnemies(collisionManager);
        enemyPool.currentEnemies(currentWave*2, resolution, collisionManager);
        waveClock.restart();
    }
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
    enemyPool.render(*window);
    player->render(*window); //player
    
    window->display();
}