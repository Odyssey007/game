#pragma once
#include "../header/utility.h"
#include "../header/battle/player/abilities/ability.h"

class Dash : public Ability {
private:
    float totalDashDistance;
    float dashDistance;
public:
    Dash();
    //void activate(sf::Sprite& player, const sf::Vector2f velocity, 
//                  const sf::Vector2f& mousePosition, const sf::Vector2f& playerPosition);
    void reset();


    virtual void activate(const sf::Vector2f& mousePosition, const sf::Vector2f& playerPosition) override;
};