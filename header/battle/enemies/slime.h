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
    //hit box
    CircleCollision hitBox;
    //current ability in use
    bool firstAttack;
    //leap attack
    bool leaping; //charging buffer for leap
    float chargeTimer;
    bool needToRecover; //recovery buffer for leap
    float recoveryTimer;
    float leapDistance; //leap distance
    float totalLeapDistance;

    virtual void attacks() override;
    void normalAttack();
    void leapAttack();
public:
    //constructor
    Slime();
    //functions
    virtual void update(const sf::Vector2f& target) override; 
    static void playerContact(Player& player, Entity& slime);
    //ENTITY fetchers
    virtual sf::FloatRect getBounds() const override;
    virtual sf::Vector2f getPosition() const override;
    //ENTITY functions
    virtual void render(sf::RenderWindow& window) const override;
};