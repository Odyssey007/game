#pragma once
#include "../header/utility.h"
#include "../header/enemies/enemy.h"
#include "../header/collision.h"
#include "../header/player/player.h"

class Goblin : public Enemy {
private:
    BoxCollision hitBox;
public:
    Goblin();
    virtual void update(const sf::Vector2f& target) override;
    static void playerContact(Player& player, Entity& slime);
    //ENTITY fetchers
    virtual sf::FloatRect getBounds() const override;
    virtual sf::Vector2f getPosition() const override;
    //ENTITY functions
    virtual void render(sf::RenderWindow& window) const override;
    virtual void attacks() override;

    bool facingRight;
    bool isMoving;
};