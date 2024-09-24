#include "../header/battle/enemies/goblin.h"

class GoblinMiniBoss : public Enemy {
private:
    //mini
    float scale;
    //ability1: blink
    bool shouldBlink;
    float cooldown;
    float cooldownAfter;
    //
    BoxCollision hitBox;
    sf::Vector2f debuff;
    //
    void blinkBehind(const sf::Vector2f& target);
    virtual void checkLvlUp(const size_t level) override;
public:
    GoblinMiniBoss();
    //ENEMY functions
    virtual void update(const sf::Vector2f& target) override; 
    virtual sf::Vector2f attack() override;
    //ENTITY fetchers
    virtual sf::FloatRect getBounds() const override;
    virtual sf::Vector2f getPosition() const override;
};