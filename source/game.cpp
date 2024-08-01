#include "../header/game.h"

//preset values into setting up window
Game::Game() : 
    //window setup
    window(nullptr), resolution(sf::Vector2u(0, 0)),
    quadTree(sf::FloatRect(0, 0, 1920, 1080), 7),
    //entities
    player(std::make_shared<Player>()), 
    enemyPool(EnemyType::SLIME, 100), currentWave(1), waveTimer(sf::seconds(455)),
    objectPool(2), blastPool(100)
{
    //preliminaries
    currentWindow();
    //entities
    player->setInitialPosition(view); //player
    collisionManager.addEntity(player); 
    enemyPool.currentEnemies(currentWave, view, collisionManager);
    objectPool.currentObjects(2, view, collisionManager);

    gameState = GAME;
}

//sets up the window
void Game::currentWindow() {
    //window set up
    sf::VideoMode screen = sf::VideoMode::getDesktopMode();
    window = std::make_unique<sf::RenderWindow>(screen, "Project-AA", sf::Style::Fullscreen);
    view = window->getDefaultView();
    resolution = window->getSize();
    window->setFramerateLimit(120);
}

bool Game::winRunning() const {
    return window->isOpen();
}

void Game::update() {
    if (gameState == EXIT) {
        window->close();
        return;
    }
    screenPosition = sf::FloatRect(view.getCenter() - view.getSize() / 2.0f, view.getSize());
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
    enemyPool.update(playerPosition);

    if (fireCooldown.getElapsedTime().asSeconds() >= 0.15) {
        blastPool.currentBlasts(mousePosition, playerPosition);
        fireCooldown.restart();
    }
    blastPool.resetBlasts(screenPosition);

    //collision check
    collisionManager.update();
    player->applyMovement();
    enemyPool.applyMovement();
    //end game shi
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

void Game::render() {
    if (gameState == MENU) {
        menu.render(*window);
    } else {
        window->setView(view);
        window->clear();
        //entities
        objectPool.render(*window);//objects
        enemyPool.render(*window);//enemies
        player->render(*window);//player
        
        //quadTree.draw(*window);

        blastPool.render(*window);
    }
    window->display();
}

void Game::checkWave() {
    // std::cout << waveClock.getElapsedTime().asSeconds() << std::endl;
    if (enemyPool.allDead()) {
        currentWave++;
        enemyPool.resetEnemies(collisionManager);
        enemyPool.currentEnemies(currentWave*2, view, collisionManager);
        waveClock.restart();
    } else if (waveClock.getElapsedTime() >= waveTimer) {
        currentWave++;
        enemyPool.currentEnemies(currentWave*2, view, collisionManager);
        waveClock.restart();
    }
}

void Game::checkGameEnd() {
    //std::cout << player->getHealth() << std::endl;
    // if (player->getHealth() == 0) {
    //     throw std::runtime_error("Game Over\n");
    // }
}