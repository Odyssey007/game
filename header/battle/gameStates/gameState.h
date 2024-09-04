#pragma once
#include "../header/utility.h"

class GameState {
public:
    virtual ~GameState() = default;

    virtual void handleEvents(Game& game, sf::Event event) = 0;
    virtual void update(Game& game) = 0;
    virtual render(sf::RenderWindow& window) = 0;
}