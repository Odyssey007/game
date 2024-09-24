#include "../header/battle/enemies/slime.h"

class SlimeMiniBoss : public Enemy {
private:
    //mini
    float scale;
    //ability1: leap attack
    bool leaping;           //charging buffer for leap
    float leapingSpeed;     //buffers
    float chargeTimer;
    bool needToRecover; 
    float recoveryTimer;
    float leapDistance;     //distance
    float totalLeapDistance;
    //
    sf::Vector2f debuff;
    CircleCollision hitBox;
    //
    void leapAttack();
    virtual void checkLvlUp(const size_t level) override;
public:
    SlimeMiniBoss();
    //ENEMY functions
    virtual void update(const sf::Vector2f& target) override; 
    virtual sf::Vector2f attack() override;
    //ENTITY fetchers
    virtual sf::FloatRect getBounds() const override;
    virtual sf::Vector2f getPosition() const override;
};