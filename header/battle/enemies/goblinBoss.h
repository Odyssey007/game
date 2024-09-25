#pragma once
#include "../header/battle/enemies/enemyAbility.h"

class Slam : public EnemyAbility {
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
    Slam();
    bool canSlam() const;
    bool cooldown(bool& abilityActive);
    virtual void activate(const sf::Vector2f& bossPos) override;
    //ENTITY fetchers
    virtual sf::FloatRect getBounds() const override;
    virtual sf::Vector2f getPosition() const override;
    //ENTITY functions 
    virtual void render(sf::RenderWindow& window) const override;
};

class GoblinBoss : public Enemy {
private:
    //
    float scale;
    sf::Vector2f debuff;
    BoxCollision hitBox;
    //
    bool usingAbility = false;
    //ability 1
    Slam bodySlam;
    
    //ability 2

    //
    //
    virtual void checkLvlUp(const size_t level) override;
public:
    GoblinBoss();
    void addExtra(GridSystem& grid);
    //ENEMY functions
    virtual void update(const sf::Vector2f& target) override; 
    virtual sf::Vector2f attack() override;
    //ENTITY fetchers
    virtual sf::FloatRect getBounds() const override;
    virtual sf::Vector2f getPosition() const override;

    //

    virtual void render(sf::RenderWindow& window) const override;

    friend class Slam;
};