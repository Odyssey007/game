#pragma once
#include "../header/battle/gameStates/gameState.h"

class PlayingState : public GameState {
private:
    std::unique_ptr<EnemyPool> enemyPool;
    std::unique_ptr<ObstaclePool> obstaclePool;
    std::unique_ptr<PlayerUI> playerUI;
public:
    virtual void handleEvents(Game& game, sf::Event event) override;
    virtual void update(Game& game) override;
    virtual void render(sf::RenderWindow& window) override;
}