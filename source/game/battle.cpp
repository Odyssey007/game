// #include "../header/game/battle.h"

// //preset values into setting up window
// BattleState::BattleState() : 
//     //window setup
//     resolution(sf::Vector2u(0, 0)),

//     //entities
//     player(std::make_shared<Player>()), 
//     enemyPool(std::make_shared<EnemyPool>(15)),
//     obstaclePool(),
//     currentWave(7), waveTimer(sf::seconds(100)),
//     blastPool(100)
//     // enemyPool(EnemyType::SLIME, 100)
// {}

// void BattleState::enter(sf::RenderWindow& window) {
//     //preliminaries
//     // view = window.getDefaultView(); 
//     // resolution = window.getSize(); 

//     // //entities
//     // gameState = GAME;
//     // player->setInitialPosition(view); 
//     // // collisionManager.addEntity(player); 
//     // enemyPool->currentEnemies(currentWave, view, collisionManager);
//     // objectPool->currentObjects(2, view, collisionManager); 

//     // //grid initialization
//     // grid = GridSystem(sf::FloatRect(0, 0, resolution.x * 2, resolution.y * 2)); 
//     // grid.getInstances(enemyPool, objectPool, player); 
// }

// void BattleState::update(sf::RenderWindow& window, sf::Event& event) {
//     if (gameState == EXIT) {
//         window.close();
//         return;
//     }
    
//     screenPosition = sf::FloatRect(view.getCenter() - view.getSize() / 2.0f, view.getSize());
//     playerBounds = player->getBounds();
//     playerPosition = player->getPosition(); 
//     mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
//     handleEvents(window, event);
//     menu.setPosition(view);
    
//     if (gameState == MENU) {
//         menu.handleEvent(event, gameState, mousePosition);
//         return;
//     }

//     //centering camera to player
//     view.setCenter(playerBounds.left + playerBounds.width/2.0f, 
//                 playerBounds.top + playerBounds.height/2.0f);
        
//     grid.getNeighbors();

//     //update entities
//     player->update(mousePosition);
//     enemyPool->update(playerPosition);

//     grid.bufferRegion(playerPosition); 
//     grid.activeGrids(player->getBounds()); 
//     grid.updateGrids(); 
//     grid.populateQuadTree(); 

//     if (fireCooldown.getElapsedTime().asSeconds() >= 0.15) {
//         blastPool.currentBlasts(mousePosition, playerPosition);
//         fireCooldown.restart();
//     }
//     blastPool.resetBlasts(screenPosition);

//     checkWave();
//     checkGameEnd();
// }

// void BattleState::handleEvents(sf::RenderWindow& window, sf::Event& event) {
//     while(window.pollEvent(event)) {
//         if (event.type == sf::Event::KeyPressed) {
//             if (event.key.code == sf::Keyboard::LAlt) gameState = MENU;
//         }
//     }
// }

// void BattleState::checkWave() {
//     // if (enemyPool->allDead()) {
//     //     currentWave++;
//     //     enemyPool->resetEnemies(collisionManager);
//     //     enemyPool->currentEnemies(currentWave*2, view, collisionManager);
//     //     waveClock.restart();
//     // } else if (waveClock.getElapsedTime() >= waveTimer) {
//     //     currentWave++;
//     //     enemyPool->currentEnemies(currentWave*2, view, collisionManager);
//     //     waveClock.restart();
//     // }
// }

// void BattleState::checkGameEnd() {
//     //std::cout << player->getHealth() << std::endl;
//     // if (player->getHealth() == 0) {
//     //     throw std::runtime_error("Game Over\n");
//     // }
// }

// void BattleState::render(sf::RenderWindow& window) {
//     if (gameState == MENU) {
//         menu.render(window);
//     } else {
//         window.setView(view);

//         //entities
//         obstaclePool->render(window);//objects
//         enemyPool->render(window);//enemies
//         player->render(window);//player
//         blastPool.render(window);
        
//         grid.draw(window); 
//     }
// }

// void BattleState::exit() {
//     std::cout << "ok" << std::endl;
// }

// StateMode BattleState::getStateType() {
//     return BATTLE; 
// }