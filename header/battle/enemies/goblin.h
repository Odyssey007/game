#pragma once
#include "../header/utility.h"
#include "../header/battle/enemies/enemy.h"
#include "../header/battle/collision.h"
#include "../header/battle/player/player.h"

class Goblin : public Enemy {
private:
    BoxCollision hitBox;
    bool isMoving;
    bool facingRight;
    void isFacingRight();
public:
    Goblin();
    //ENEMY functions
    virtual sf::Vector2f attack() override;
    virtual void update(const sf::Vector2f& target) override;

    //ENTITY fetchers
    virtual sf::FloatRect getBounds() const override;
    virtual sf::Vector2f getPosition() const override;
    //ENTITY functions
    virtual void render(sf::RenderWindow& window) const override;
};