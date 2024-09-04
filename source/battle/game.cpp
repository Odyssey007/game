#include "../header/battle/game.h"

//preset values into setting up window
Game::Game() : 
    //window setup
    window(nullptr), resolution(sf::Vector2u(0, 0))
    //?temp
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
    abilitySelectionUI = std::make_unique<AbilitySelectionUI>();
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
        }
        if (gameState == GAME) {
            handleGameEvents();
        } else if (gameState == LEVEL_UP_MENU) {
            handleAbilityUIEvents();
        } else if (gameState == PAUSE_MENU) {
            handlePauseMenuEvents();
        }
    }
}

void Game::handleEvents() {
    while(window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) window->close();
            if (event.key.code == sf::Keyboard::LAlt) gameState = PAUSE_MENU;
        } else if (event.type == sf::Event::MouseButtonPressed) {
            sf::Mouse::Button button;
            if (event.mouseButton.button == sf::Mouse::Left) {
                button = sf::Mouse::Left;
            }
            player->checkAbility(button, mousePosition, grid);
         } else if (event.type == sf::Event::MouseButtonReleased) {
            player->setAbilityInactive();
         }
    }
}

void Game::update() {
    if (gameState == GAME) {
        gameUpdate();
    } else if (gameState == LEVEL_UP_MENU) {
        abilityUIUpdate();
    } else if (gameState == PAUSE_MENU) {
        pauseMenuUpdate();
    }




    if (gameState != GAME) return; 
    handleEvents();
    //centering camera to player
    view.setCenter(playerBounds.left + playerBounds.width/2.0f, 
                playerBounds.top + playerBounds.height/2.0f);
    //save info for the frame
    screenBounds = sf::FloatRect(view.getCenter() - view.getSize() / 2.0f, view.getSize());
    playerBounds = player->getBounds();
    playerPosition = player->getPosition(); 
    mousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    //enemy spawn
    if (waveSystem.isUpdated(enemyPool->isAllDead(), enemiesSpawning, enemyLevel)) {
        enemyPool->spawnEnemies(enemiesSpawning, enemyLevel, screenBounds, grid);
    }
    //UI updates
    playerUI->update(screenBounds, player->getHpPercentage(), 
                    player->getExpPercentage(), player->getLevel());
    
    abilitySelectionUI->update(player->getLevel(), lastLvl, gameState);

    //menu
    menu.setPosition(view);
    if (gameState == PAUSE_MENU) {
        menu.handleEvent(event, gameState, mousePosition);
        return;
    }
        

    //update entities
    player->update(mousePosition, screenBounds);
    enemyPool->update(playerPosition);
    obstaclePool->update(screenBounds);
    //collision check
    grid.checkCollision();
    player->applyMovement();
    enemyPool->applyMovement();
    obstaclePool->update(screenBounds);
    //clean up 
    player->reset();
    enemyPool->resetExp();
    enemyPool->resetEnemies(grid);
    grid.removeDeadEntities();
    //update gridSys
    grid.bufferRegion(playerPosition); 
    grid.activeGrids(player->getBounds()); 
    grid.updateGrids();     
    grid.populateQuadTree(); 
    //
    if (gameState == LEVEL_UP_MENU) abilitySelectionUI->spawnCards(screenBounds);
    //end game
    checkGameEnd();
}

void Game::checkGameEnd() {
    // std::cout << player->getHealth() << std::endl;
    // if (player->getHealth() == 0) {
    //     throw std::runtime_error("Game Over\n");
    // }
}

void Game::render() {
    if (gameState == GAME) {
        window->setView(view);
        window->clear();
        //entities
        enemyPool->render(*window);
        player->render(*window);
        // blastPool.render(*window);
        obstaclePool->render(*window);
        //UI
        playerUI->render(*window);
        //quadTree.draw(*window);
        // grid.draw(*window); 
    } else if (gameState == LEVEL_UP_MENU) {
        abilitySelectionUI->render(*window);
    } else if (gameState == PAUSE_MENU) {
        menu.render(*window);
    }
    window->display();
}