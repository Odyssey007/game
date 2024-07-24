#include "../header/game.h"

//preset values into setting up window
Game::Game() : 
    //window setup
    window(nullptr), resolution(sf::Vector2u(0, 0)),
    quadTree(sf::FloatRect(0, 0, 1920*2, 1080*2), 5),
    //entities
    player(std::make_shared<Player>()), 
    enemyPool(EnemyType::SLIME, 100), currentWave(5), waveTimer(sf::seconds(10000)),
    objectPool(2)
{
    //preliminaries
    currentWindow();
    //entities
    player->setInitialPosition(sf::Vector2u(resolution.x/2, resolution.y/2)); //player
    collisionManager.addEntity(player); 
    enemyPool.currentEnemies(currentWave, resolution, collisionManager);
    objectPool.currentObjects(1, collisionManager);
    //grid initialization
    grid = Grid(sf::FloatRect(0, 0, resolution.x * 2, resolution.y * 2)); 
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
    //centering camera to player
    sf::FloatRect playerBounds = player->getBounds();
    view.setCenter(playerBounds.left + playerBounds.width/2.0f, 
                   playerBounds.top + playerBounds.height/2.0f);
    //update entities
    sf::Vector2f playerPosition = player->getPosition(); 
    sf::Vector2f mousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    player->update(mousePosition);
    enemyPool.update(playerPosition);
    //collision check
    collisionManager.update();
    player->applyMovement();
    enemyPool.applyMovement();
    //
    // if(!quadTree.windowBounds.intersects(playerBounds)) {
    //     quadTree.updateBounds(mousePosition); 
    // }
    // quadTree.clear(); 
    // quadTree.insertObject(playerBounds); 
    // for(auto& slime : enemyPool.activeEnemies) {
    //     quadTree.insertObject(slime->getBounds()); 
    // }
    //
    grid.bufferRegion(view); 
    checkWave();
    checkGameEnd();
}

void Game::checkWave() {
    // std::cout << waveClock.getElapsedTime().asSeconds() << std::endl;
    if (enemyPool.allDead()) {
        currentWave++;
        enemyPool.resetEnemies(collisionManager);
        enemyPool.currentEnemies(currentWave*2, resolution, collisionManager);
        waveClock.restart();
    } else if (waveClock.getElapsedTime() >= waveTimer) {
        currentWave++;
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
    objectPool.render(*window);//objects
    enemyPool.render(*window);//enemies
    player->render(*window);//player
    
    
    //quadTree.draw(*window);
    grid.draw(*window); 
    
    window->display();
}