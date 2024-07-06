#pragma once
#include "utility.h"
#include "enemy.h"
#include "collision.h"
#include "player.h"

//currentAbility: 0 - NONE | 1 - NORMAL | 2 - LEAP
class Player;

class Slime : public Enemy {
private:
    //hit box
    CircleCollision hitBox;
    //current ability in use
    int currentAbility;
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
    void update(const sf::Vector2f& target, const float attackRange);
    virtual void render(sf::RenderWindow& window) override;
    static void playerContact(Player& player, Entity& slime);
    //fetcher functions
    virtual size_t getState() override;
    virtual sf::Shape& getShape() override;
};