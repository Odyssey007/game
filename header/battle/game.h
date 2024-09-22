#pragma once
//game engine
#include "../header/utility.h"
#include "../header/battle/collisionManager.h"
#include "../header/battle/player/player.h"
#include "../header/battle/enemies/slime.h"
#include "../header/battle/obstacles/pillar.h"
#include "../header/battle/player/abilities/ability.h"
#include "../header/battle/gridSystem.h"
#include "../header/battle/pool.h"

#include "../header/battle/menu.h"

#include "../header/battle/enemies/exp.h"
#include "../header/battle/waveSystem.h"


#include "../header/battle/player/playerUI.h"
#include "../header/battle/player/abilities/abilitySelectionUI.h"

//remove
#include "../header/battle/enemies/slimeMiniBoss.h"


class Game {
private:
    sf::Texture backgroundTexture;
    sf::Sprite spriteBackground;
    //set up
    std::unique_ptr<sf::RenderWindow> window; 
    sf::View view;
    sf::Event event;
    GridSystem grid;
    GameState gameState;
    //info storage
    sf::FloatRect screenBounds;
    sf::Vector2f mousePosition;
    sf::Vector2f playerPosition;
    sf::FloatRect playerBounds;
    //entities
    std::unique_ptr<Player> player;
    std::unique_ptr<EnemyPool> enemyPool;
    std::unique_ptr<ObstaclePool> obstaclePool;
    //UI
    std::unique_ptr<PlayerUI> playerUI;
    uint8_t lastLvl; bool skipFrame;
    std::unique_ptr<AbilitySelectionUI> abilitySelectionUI;
    //wave
    size_t enemiesSpawning; size_t enemyLevel;
    WaveSystem waveSystem;
    //functions
    void currentWindow();
    void handleEvents();
    //game states
    void handleEventsPlaying();
    void handleEventsLevelUp();
    void handleEventsPause();
    void updatePlaying();
    void updateLevelUp();
    void updatePause();
    void renderPlaying();
    void renderLevelUp();
    void renderPause();
public:
    //constructor
    Game();
    //functions
    void update();
    void render();
    bool winRunning() const;
    void isGameOver() const;


    //!not finalized
    //pause menu
    Menu menu;

    std::unique_ptr<SlimeMiniBoss> miniBoss;
};

/*
sf::Clock worldTime;  
sf::Time elapsed = worldTime.getElapsedTime();

int minutes = static_cast<int>(elapsed.asSeconds()) / 60;
int seconds = static_cast<int>(elapsed.asSeconds()) % 60;
*/