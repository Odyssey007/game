#pragma once
#include "../header/utility.h"
#include "../header/battle/player/abilities/ability.h"

class EnergyBarrier : public Ability {
private:
    bool active;
    uint8_t state;
    sf::Vector2u debuff;
    CircleCollision hitBox;
    //enlarge
    float curScale;
    float targetScale;
    float elapsedTime;
    float scaleDuration;
    //pulse
    float pulseElapsed;
    float frequency;
    float minScale;
    float maxScale;
    //
    sf::Clock timer;
    void enlarge();
    void pulse();
    void reset();
    sf::FloatRect calcBounds(float scale);
public:
    EnergyBarrier() = default;
    EnergyBarrier(GridSystem& grid);
    void activate(const sf::Vector2f& playerPos, bool facingRight, bool moving) override;
    void update(uint8_t& numHits) override;

    virtual sf::Vector2u hitEnemy() override; //returns dmg
    virtual sf::FloatRect getBounds() const override;
};