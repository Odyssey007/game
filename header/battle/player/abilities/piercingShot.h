#pragma once
#include "../header/utility.h"
#include "../header/battle/player/abilities/ability.h"

class PiercingShotManager;

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
    void movement(const sf::Vector2f& target);
    //
    friend class PiercingShotManager;
public:
    PiercingShot();
    //movements
    sf::Vector2f calcStartPos(const sf::Vector2f& playerPosition, bool playerFacingRight, size_t num);
    virtual void activate(const sf::Vector2f& toEnemy) override; //go forward
    void goBack(const sf::Vector2f& toRest); //come back
    void restPosition(const sf::Vector2f& restPosition); //follow around
    void animateMovement();
    void afterHitBuffer();
    //
    virtual sf::Vector2u hitEnemy() override; //returns dmg
    //ENTITY
    virtual sf::FloatRect getBounds() const override;
};

class PiercingShotManager {
private:
    float fireRange;
    size_t numShots;
    std::vector<std::unique_ptr<PiercingShot>> shots;
    //buffer
    float timerBeforeStart = 0.0f;
    float cooldownBeforeStart = 0.5f;
public:
    PiercingShotManager(GridSystem& grid);
    //
    void activate(const sf::Vector2f& target, const sf::Vector2f& playerPos);
    void update(const sf::Vector2f& target, const sf::Vector2f& playerPos, bool playerFacingRight);
    bool startBuffer();
    //
    void render(sf::RenderWindow& window) const;
};