#include "../header/battle/game.h"

//preset values into setting up window
Game::Game() {
    //preliminaries
    window = nullptr; gameState = PLAYING; currentWindow();
    grid = GridSystem(sf::FloatRect(0, 0, screenBounds.width * 2, screenBounds.height * 2)); 
    //entity construction
    enemyPool = std::make_unique<EnemyPool>(100);
    player = std::make_unique<Player>();
    obstaclePool = std::make_unique<ObstaclePool>(5, screenBounds, grid);
    //wave set up
    enemiesSpawning = 1; enemyLevel = 0;
    //entity initial update
    player->setInitialPosition(screenBounds); grid.addEntity(*player);
    enemyPool->spawnEnemies(enemiesSpawning, enemyLevel, screenBounds, grid);
    //UI
    playerUI = std::make_unique<PlayerUI>(screenBounds.width);
    lastLvl = 1; skipFrame = false;
    abilitySelectionUI = std::make_unique<AbilitySelectionUI>();


    backgroundTexture.loadFromFile("assets/background.png");
    spriteBackground.setTexture(backgroundTexture);

    // miniBoss = std::make_unique<GoblinBoss>();
    // miniBoss->spawn(1, screenBounds);
    // grid.addEntity(*miniBoss);
    // miniBoss->addExtra(grid);
}

//window set up
void Game::currentWindow() {
    sf::VideoMode screen = sf::VideoMode::getDesktopMode();
    window = std::make_unique<sf::RenderWindow>(screen, "Project-AA", sf::Style::Fullscreen);
    view = window->getDefaultView();
    window->setFramerateLimit(120);
    screenBounds = sf::FloatRect(view.getCenter() - view.getSize() / 2.0f, view.getSize());
    // window->setMouseCursorVisible(false); //!don't work
}

bool Game::winRunning() const {
    return window->isOpen();
}

void Game::handleEvents() {
    while(window->pollEvent(event)) {
        //valid across each state
        if (event.type == sf::Event::Closed) {
            window->close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) window->close();
        }
        //
        switch (gameState) {
            case PLAYING:
                handleEventsPlaying();
                break;
            case LEVEL_UP_MENU:
                handleEventsLevelUp();
                break;
            case PAUSE_MENU:
                handleEventsPause();
                break;
        }
    }
}

void Game::handleEventsPlaying() {
    if (event.type == sf::Event::KeyPressed) {
        sf::Keyboard::Key key = event.key.code;
        if (key == sf::Keyboard::LAlt) {
            gameState = PAUSE_MENU;
        } else {
            player->updateAbilities(key, mousePosition, grid);
        }
    } else if (event.type == sf::Event::MouseButtonPressed) {
        sf::Mouse::Button button = event.mouseButton.button;
        player->updateAbilities(button, mousePosition, grid);
    } else if (event.type == sf::Event::MouseButtonReleased || event.type == sf::Event::KeyReleased) {
        player->setAbilityInactive();
    }
}

void Game::handleEventsLevelUp() {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Mouse::Button button = event.mouseButton.button;
        abilitySelectionUI->confirmAbility(button, mousePosition, gameState);
    }
}

void Game::handleEventsPause() {
    return;
}

void Game::update() {
    //preliminaries
    view.setCenter(playerBounds.left + playerBounds.width/2.0f, //centering camera to player 
                   playerBounds.top + playerBounds.height/2.0f);
        //save info for the frame
    screenBounds = sf::FloatRect(view.getCenter() - view.getSize() / 2.0f, view.getSize());
    playerBounds = player->getBounds();
    playerPosition = player->getPosition(); 
    mousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    handleEvents();
    //
    switch (gameState) {
        case PLAYING:
            updatePlaying();
            break;
        case LEVEL_UP_MENU:
            updateLevelUp();
            break;
        case PAUSE_MENU:
            updatePause();
            break;
    }
}

void Game::updatePlaying() {
    // miniBoss->checkAlive();
    // if (miniBoss->isAlive()) {
    //     miniBoss->update(playerPosition);
    //     miniBoss->checkAlive();
    //     miniBoss->updateAbility(playerPosition, screenBounds, grid);
    // }

    //enemy spawn: checks if a new wave needs to spawn
    if (waveSystem.isUpdated(enemyPool->isAllDead(), enemiesSpawning, enemyLevel)) {
        enemyPool->spawnEnemies(enemiesSpawning, enemyLevel, screenBounds, grid);
    }
    //update entities
    obstaclePool->update(screenBounds);
    player->update(mousePosition, screenBounds, grid);
    enemyPool->update(playerPosition);
    //collision check
    grid.checkCollision();

    // miniBoss->applyMovement();

    player->applyMovement();
    enemyPool->applyMovement();
    player->tempSol(); //?hack fix later
    //clean up 
    
    // miniBoss->abilityCleanUp();

    player->cleanUpAbilities(grid);
    enemyPool->resetEnemies(grid);
    grid.removeDeadEntities();
    //update gridSys
    grid.bufferRegion(playerPosition); 
    grid.activeGrids(player->getBounds()); 
    grid.updateGrids();     
    grid.populateQuadTree();
    //UI updates
    playerUI->update(screenBounds, player->getHpPercentage(), 
                    player->getExpPercentage(), player->getLevel());    
    abilitySelectionUI->update(player->getLevel(), lastLvl, gameState);
    if (gameState == LEVEL_UP_MENU) {
        abilitySelectionUI->spawnCards(screenBounds);
        skipFrame = true;
    }
    player->abilityFactory(grid);
}

void Game::updateLevelUp() {
    // abilitySelectionUI->spawnCards(screenBounds);
    // skipFrame = true;
}

void Game::updatePause() {
    menu.setPosition(view);
    menu.handleEvent(event, gameState, mousePosition);
}

void Game::isGameOver() const {
    if (player->getCurHealth() <= 0) {
        std::cout << "ni hao\n"; // throw std::runtime_error("Game Over\n");
    }
}

void Game::render() {
    if (gameState == PLAYING || skipFrame == true) {
        renderPlaying();
    } else if (gameState == LEVEL_UP_MENU) {
        renderLevelUp();
    } else if (gameState == PAUSE_MENU) {
        renderPause();
    }
    window->display();
}

void Game::renderPlaying() {
    skipFrame = false; //in case needs to update for UI
    window->clear();
    window->setView(view);
    //entities
    player->renderAbilities(*window);
    enemyPool->renderEnemies(*window);
    enemyPool->renderExp(*window);
    player->render(*window);
    obstaclePool->render(*window);
    //UI
    playerUI->render(*window);
    // grid.draw(*window);

}

void Game::renderLevelUp() {
    abilitySelectionUI->render(*window);
}

void Game::renderPause() {
    menu.render(*window);
}