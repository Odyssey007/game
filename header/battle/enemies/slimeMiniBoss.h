#include "../header/battle/enemies/slime.h"

class SlimeMiniBoss : public Enemy {
private:
    float scale;
    sf::Vector2u debuff;
    //hit box
    bool facingRight;
    CircleCollision hitBox;
    //leap attack
    float leapingSpeed;
    bool leaping; //charging buffer for leap
    float chargeTimer;
    bool needToRecover; //recovery buffer for leap
    float recoveryTimer;
    float leapDistance; //leap distance
    float totalLeapDistance;
    virtual void checkLvlUp(const size_t level) override;
public:
    SlimeMiniBoss();
    void leapAttack();
    //functions
    virtual void update(const sf::Vector2f& target) override; 
    virtual sf::Vector2u attack() override;
    //ENTITY fetchers
    virtual sf::FloatRect getBounds() const override;
    virtual sf::Vector2f getPosition() const override;
    //ENTITY functions
    virtual void render(sf::RenderWindow& window) const override;
};