#include "../header/battle/game.h"

//preset values into setting up window
Game::Game() : 
    //window setup
    window(nullptr), resolution(sf::Vector2u(0, 0)),
    //?temp
    blastPool(100)
{
    //preliminaries
    currentWindow(); gameState = GAME;
    grid = GridSystem(sf::FloatRect(0, 0, resolution.x * 2, resolution.y * 2)); 
    //entity construction
    player = std::make_unique<Player>();
    enemyPool = std::make_unique<EnemyPool>(100);
    obstaclePool = std::make_unique<ObstaclePool>(5, screenBounds, grid);
    //entity starting update
    player->setInitialPosition(screenBounds); grid.addEntity(*player);
    enemyPool->spawnEnemies(enemiesSpawning, enemyLevel, screenBounds, grid);
    //UI
    playerUI = std::make_unique<PlayerUI>(screenBounds.width);
}

//window set up
void Game::currentWindow() {
    sf::VideoMode screen = sf::VideoMode::getDesktopMode();
    window = std::make_unique<sf::RenderWindow>(screen, "Project-AA", sf::Style::Fullscreen);
    view = window->getDefaultView();
    resolution = window->getSize();
    window->setFramerateLimit(120);
    screenBounds = sf::FloatRect(view.getCenter() - view.getSize() / 2.0f, view.getSize());
    // window->setMouseCursorVisible(false); //!don't work
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
                blastPool.spawnBlasts(grid, abilityActive, mousePosition, playerPosition);
            }
         } else if (event.type == sf::Event::MouseButtonReleased) {
            abilityActive = false;
         }
    }
}

void Game::update() {
    if (gameState == EXIT) {
        window->close();
        return;
    }

    //centering camera to player
    view.setCenter(playerBounds.left + playerBounds.width/2.0f, 
                playerBounds.top + playerBounds.height/2.0f);

    screenBounds = sf::FloatRect(view.getCenter() - view.getSize() / 2.0f, view.getSize());
    playerBounds = player->getBounds();
    playerPosition = player->getPosition(); 
    mousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    
    if (waveSystem.isUpdated(enemyPool->isAllDead(), enemiesSpawning, enemyLevel)) {
        enemyPool->spawnEnemies(enemiesSpawning, enemyLevel, screenBounds, grid);
    }

    playerUI->update(screenBounds, player->getHpPercentage(), 
                    player->getExpPercentage(), player->getLevel());



    handleEvents();
    menu.setPosition(view);

    if (gameState == MENU) {
        menu.handleEvent(event, gameState, mousePosition);
        return;
    }
        

    //update entities
    float mouseDirection = (screenBounds.left + screenBounds.width/2.0f);
    player->movement(mousePosition, mouseDirection, abilityActive);
    // player->update(mousePosition, screenBounds);


    
    enemyPool->update(playerPosition);
    obstaclePool->update(screenBounds);
    //ability
    blastPool.onScreen(screenBounds);


    grid.checkCollision();
    player->applyMovement();
    enemyPool->applyMovement();
    obstaclePool->update(screenBounds);
    

    blastPool.update();
    enemyPool->resetEnemies(grid);
    enemyPool->resetExp();
    grid.removeDeadEntities();

    grid.bufferRegion(playerPosition); 
    grid.activeGrids(player->getBounds()); 
    grid.updateGrids();     
    grid.populateQuadTree(); 
    


    //abilities
 
    checkGameEnd();
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
        //entities
        enemyPool->render(*window);//enemies
        player->render(*window);//player
        
        //quadTree.draw(*window);

        blastPool.render(*window);

        obstaclePool->render(*window);//objects
        
        playerUI->render(*window);
        // grid.draw(*window); 
    }
    window->display();
}