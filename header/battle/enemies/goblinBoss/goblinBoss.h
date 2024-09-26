#pragma once
#include "../header/battle/enemies/goblinBoss/bodySlam.h"
#include "../header/battle/enemies/goblinBoss/bulletSpray.h"

class GoblinBoss : public Enemy {
private:
    //
    float scale;
    sf::Vector2f debuff;
    BoxCollision hitBox;
    //
    bool usingAbility = false;
    //ability 1
    BodySlam bodySlam;    
    //ability 2
    BulletSprayPool bullet;
    //
    virtual void checkLvlUp(const size_t level) override;
public:
    void updateAbility(GridSystem& grid, const sf::FloatRect& screenBounds);
    void abilityCleanUp();
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