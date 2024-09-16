#pragma once
#include "../header/utility.h"
#include "../header/battle/player/abilities/ability.h"

class EnergyBarrier : public Ability {
private:
    uint8_t state;
    sf::Vector2u debuff;
    //
    bool active = false;
    //
    CircleCollision hitBox;
    //
    sf::Clock timer;
public:
    EnergyBarrier();
    void activate(const sf::Vector2f& playerPos, bool facingRight, bool moving);
    void update(uint8_t& numHits);
    sf::FloatRect calcBounds(float scale);
    
    float curScale = 2.3f;
    float targetScale = 15.0f;
    float elapsedTime = 0.0f;
    float scaleDuration = 0.5f;
    void enlarge();
    float pulseElapsed = 0.0f;
    float frequency = 10.1f;
    float minScale = 2.3f;
    float maxScale = 3.f;
    void pulse();
    void reset();
    virtual sf::Vector2u hitEnemy() override; //returns dmg
    virtual void render(sf::RenderWindow& window) const override;
};