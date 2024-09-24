#pragma once
#include "../header/utility.h"
#include "../header/battle/enemies/enemy.h"
#include "../header/battle/collision.h"
#include "../header/battle/collisionManager.h"
#include "../header/battle/player/player.h"

//currentAbility: 0 - NONE | 1 - NORMAL | 2 - LEAP
class Player;

class Slime : public Enemy {
private:
    //
    sf::Vector2f debuff;
    CircleCollision hitBox;
    //
    virtual void checkLvlUp(const size_t level) override;
public:
    Slime();
    //ENEMY functions
    virtual void update(const sf::Vector2f& target) override; 
    virtual sf::Vector2f attack() override;
    //ENTITY fetchers
    virtual sf::FloatRect getBounds() const override;
    virtual sf::Vector2f getPosition() const override;
};