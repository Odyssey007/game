#pragma once
#include "../header/battle/enemies/enemyAbility.h"

class BodySlam : public EnemyAbility {
private:
    //
    sf::CircleShape sprite;
    sf::CircleShape maxSizeOutline;
    CircleCollision hitBox;
    //buffer
    bool shouldSlam;
    float slamCooldown;
    float afterSlamCooldown;
    //increase size 
    float slamEnlargeTime;
    float slamEnlargeDuration;
    float curSize;
    float maxSize;
    //finish
    bool finishedCasting;
    float dmgDuration;
    //
    sf::FloatRect calcBounds(float scale);
public:
    BodySlam();
    bool canSlam() const;
    bool cooldown(bool& abilityActive);
    virtual void activate(const sf::Vector2f& bossPos) override;
    //ENTITY fetchers
    virtual sf::FloatRect getBounds() const override;
    virtual sf::Vector2f getPosition() const override;
    //ENTITY functions 
    virtual void render(sf::RenderWindow& window) const override;
};