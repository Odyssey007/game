#include "../header/battle/game.h"

//preset values into setting up window
Game::Game() : 
    //window setup
    window(nullptr), resolution(sf::Vector2u(0, 0)),
    //entities
    player(std::make_unique<Player>()), 
    enemyPool(std::make_unique<EnemyPool>(100)),
    obstaclePool(std::make_unique<ObstaclePool>(5)),
    currentWave(1), waveTimer(sf::seconds(50)),
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
    //!shit don't work
    // window->setMouseCursorVisible(false);
    //
    backgroundTexture.loadFromFile("assets/background.png");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(sf::Vector2f(1.8f, 1.8f));
}

bool Game::winRunning() const {
    return window->isOpen();
}

void Game::handleEvents() {
    while(window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) window->close();
            if (event.key.code == sf::Keyboard::LAlt) gameState = MENU;
        } else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                    blastPool.currentBlasts(mousePosition, playerPosition, grid);
            }
         }
    }
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
    
    std::cout << player->getPosition().x << ", " << player->getPosition().y << std::endl;
    handleEvents();
    menu.setPosition(view);

    backgroundSprite.setPosition(screenBounds.left, screenBounds.top);
    
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
    //ability
    blastPool.update(screenBounds);


    grid.checkCollision();
    player->applyMovement();
    enemyPool->applyMovement();
    obstaclePool->update(screenBounds);
    
    blastPool.resetBlasts();
    enemyPool->resetEnemies();
    grid.removeDeadEntities();

    grid.bufferRegion(playerPosition); 
    grid.activeGrids(player->getBounds()); 
    grid.updateGrids(); 
    grid.populateQuadTree(); 
    


    //abilities
 
    checkWave();
    checkGameEnd();
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
    // std::cout << player->getHealth() << std::endl;
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
        //background
        window->draw(backgroundSprite);
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