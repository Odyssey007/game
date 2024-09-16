#pragma once
#include "../header/utility.h"
#include "../header/battle/player/abilities/ability.h"

class PiercingShotManager;

//TODO slow | reduced dmg on the way back 
class PiercingShot : public Ability {
private:
    CircleCollision hitBox;
    sf::Vector2u debuff;
    //checks
    bool active; 
    bool revert;
    bool hit;
    //buffer
    float timerAfterHit;
    float cooldownAfterHit;
    //movement
    sf::Vector2f move;
    float speed;
    //
    sf::Vector2f calcStartPos(const sf::Vector2f& playerPosition, bool playerFacingRight, size_t num);
    virtual void activate(const sf::Vector2f& toEnemy) override; //go forward
    void restPosition(const sf::Vector2f& restPosition); //follow around
    void applyMovement(const sf::Vector2f& target);
    void goBack(const sf::Vector2f& toRest); //come back
    void animateMovement();
    void afterHitBuffer();
    // PARENT
    virtual sf::Vector2u hitEnemy() override; // ABILITY
    virtual sf::FloatRect getBounds() const override; //ENTITY
    //
    friend class PiercingShotManager;
public:
    PiercingShot();
};

class PiercingShotManager : public Ability {
private:
    float fireRange;
    size_t numShots;
    std::vector<std::unique_ptr<PiercingShot>> shots;
    //buffer
    float timerBeforeStart;
    float cooldownBeforeStart;
    bool startBuffer();
public:
    PiercingShotManager(GridSystem& grid);
    //
    virtual void update(const sf::Vector2f& target, const sf::Vector2f& playerPos, bool playerFacingRight) override;
    virtual void activate(const sf::Vector2f& target, const sf::Vector2f& playerPos) override;
    virtual void render(sf::RenderWindow& window) const override;
};