#pragma once
#include "../header/utility.h"
#include "../header/player/abilities/ability.h"

class Slash : public Ability {
private: 
    SlashShape hitBoxSlash;

    void slashSpriteRotation(float angle, sf::Vector2f position); 
    void updateSlashTime();

public:
    bool slashVisible;
    bool facingRight;
    float slashAngle;
    float slashTime;  
    //constructor
    Slash();
    ~Slash() = default;
    //functions
    virtual void activate(const sf::Vector2f& mousePosition, const sf::Vector2f& playerPosition) override;
    virtual void render(sf::RenderWindow& window) const override;
};