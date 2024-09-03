#pragma once
#include "../header/utility.h"
#include "../header/battle/entity.h"
#include "../header/animation.h"
#include "../header/battle/enemies/slime.h"
#include "../header/battle/player/abilities/basicSlash.h"
#include "../header/battle/player/abilities/dash.h"

class Player : public Entity {
private:
    //texture
    sf::Texture texture;
    sf::Sprite sprite;
    //animation
    Animation animation;
    sf::Vector2u animationSheetDim;
    float frameDuration;
    //stats
    float health;
    float battleSpeed;
    const float kingdomSpeed;
    float exp;
    float expRequired;
    unsigned int level;
    std::vector<std::shared_ptr<Ability>> abilities;
    //hit box
    BoxCollision hitBox;
    sf::FloatRect bounds;
    //player movement
    sf::Vector2f moveDistance;
    bool isMoving;
    bool facingRight;
    //collision handling
    void handleEnemyCollisions(Entity& other);
    void handleExpCollision(Entity& other);
    void checkLevelUp(float exp);
public:
    //constructor
    Player(); 
    //fetchers
    float getHealth();
    //functions
    void update(const sf::Vector2f& mousePosition, const sf::FloatRect& screenBounds);
    void takeDebuffs(const sf::Vector2f& debuff);
    //ENTITY fetchers
    virtual sf::FloatRect getBounds() const override;
    virtual sf::Vector2f getPosition() const override;
    virtual const sf::Vector2f& getVelocity() const override;
    //ENTITY setters
    virtual void setVelocity(const sf::Vector2f& velocity) override;
    virtual void setInitialPosition(const sf::FloatRect& screenBounds) override;
    //ENTITY functions
    virtual void applyMovement() override;
    virtual void handleCollision(Entity& other) override;
    virtual void render(sf::RenderWindow& window) const override;



    void movement(const sf::Vector2f& mousePosition, float mouseDirection, bool abilityActive);
    void idle(const sf::Vector2f& mousePosition, float mouseDirection);



    bool isDashing = false;
    float dashCooldown = 0.5f;
    sf::Clock dashClock;
    float totalDashDistance = 0;
    float dashDistance = 300;
    void dash(const sf::Vector2f& mousePosition);
};