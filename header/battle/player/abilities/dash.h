#pragma once
#include "../header/utility.h"
#include "../header/battle/player/abilities/ability.h"

class Dash {
private:
    sf::Clock activeCooldown;
    float fireCooldown;
    float teleportRange;
public:
    Dash();
    bool activate(const sf::Vector2f& mousePosition, sf::Vector2f& playerPosition);
};