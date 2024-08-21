#include "../header/battle/game.h"

//preset values into setting up window
Game::Game() : 
    //window setup
    window(nullptr), resolution(sf::Vector2u(0, 0)),
    //entities
    player(std::make_unique<Player>()), 
    enemyPool(std::make_unique<EnemyPool>(100)),
    obstaclePool(std::make_unique<ObstaclePool>(4)),
    currentWave(2), waveTimer(sf::seconds(50)),
    blastPool(100)
{
    //preliminaries
    currentWindow();
    grid = GridSystem(sf::FloatRect(0, 0, resolution.x * 2, resolution.y * 2)); 
    //entities
    gameState = GAME;
    player->setInitialPosition(screenBounds); //player
    grid.addEntity(*player);
    // obstaclePool = std::make_unique<ObstaclePool>(grid, screenBounds);
    enemyPool->currentEnemies(currentWave, screenBounds, grid);
    obstaclePool->currentObjects(screenBounds, grid);
}

//sets up the window
void Game::currentWindow() {
    //window set up
    sf::VideoMode screen = sf::VideoMode::getDesktopMode();
    window = std::make_unique<sf::RenderWindow>(screen, "Project-AA", sf::Style::Fullscreen);
    view = window->getDefaultView();
    resolution = window->getSize();
    window->setFramerateLimit(120);
    screenBounds = sf::FloatRect(view.getCenter() - view.getSize() / 2.0f, view.getSize());
}

bool Game::winRunning() const {
    return window->isOpen();
}

void Game::update() {
    if (gameState == EXIT) {
        window->close();
        return;
    }
    screenBounds = sf::FloatRect(view.getCenter() - view.getSize() / 2.0f, view.getSize());
    playerBounds = player->getBounds();
    playerPosition = player->getPosition(); 
    mousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    
    handleEvents();
    menu.setPosition(view);
    
    if (gameState == MENU) {
        menu.handleEvent(event, gameState, mousePosition);
        return;
    }

    //centering camera to player
    view.setCenter(playerBounds.left + playerBounds.width/2.0f, 
                playerBounds.top + playerBounds.height/2.0f);
        

    //update entities
    player->update(mousePosition);
    enemyPool->update(playerPosition);
    obstaclePool->update(screenBounds);

    grid.checkCollision();
    player->applyMovement();
    enemyPool->applyMovement();
    


    grid.bufferRegion(playerPosition); 
    grid.activeGrids(player->getBounds()); 
    grid.updateGrids(); 
    grid.populateQuadTree(); 
    


    //collision check

    if (fireCooldown.getElapsedTime().asSeconds() >= 0.15) {
        blastPool.currentBlasts(mousePosition, playerPosition);
        fireCooldown.restart();
    }
    blastPool.resetBlasts(screenBounds);

 
    checkWave();
    checkGameEnd();
}

void Game::handleEvents() {
    while(window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) window->close();
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) window->close();
            if (event.key.code == sf::Keyboard::LAlt) gameState = MENU;
        }
    }
}


void Game::checkWave() {
    // std::cout << waveClock.getElapsedTime().asSeconds() << std::endl;
    // if (enemyPool->allDead()) {
    //     currentWave++;
    //     enemyPool->resetEnemies(collisionManager);
    //     enemyPool->currentEnemies(currentWave*2, view, collisionManager);
    //     waveClock.restart();
    // } else if (waveClock.getElapsedTime() >= waveTimer) {
    //     currentWave++;
    //     enemyPool->currentEnemies(currentWave*2, view, collisionManager);
    //     waveClock.restart();
    // }
}

void Game::checkGameEnd() {
    //std::cout << player->getHealth() << std::endl;
    // if (player->getHealth() == 0) {
    //     throw std::runtime_error("Game Over\n");
    // }
}

void Game::render() {
    if (gameState == MENU) {
        menu.render(*window);
    } else {
        window->setView(view);
        window->clear();
        //entities
        enemyPool->render(*window);//enemies
        player->render(*window);//player
        
        //quadTree.draw(*window);

        blastPool.render(*window);
        
        obstaclePool->render(*window);//objects
        // grid.draw(*window); 
    }
    window->display();
}