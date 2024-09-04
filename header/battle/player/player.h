#pragma once
#include "../header/utility.h"
#include "../header/battle/entity.h"
#include "../header/animation.h"
#include "../header/battle/enemies/slime.h"
#include "../header/battle/player/abilities/basicSlash.h"
#include "../header/battle/player/abilities/dash.h"
#include "../header/battle/player/abilities/blast.h"

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
    int healthMax;
    int health;
    float battleSpeed;
    const float kingdomSpeed;
    int exp;
    int expRequired;
    uint8_t level;
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
    uint8_t getLevel() const;
    float getHpPercentage() const;
    float getExpPercentage() const;
    //functions
    void update(const sf::Vector2f& mousePosition, const sf::FloatRect& screenBounds);
    void takeDebuffs(const sf::Vector2u& debuff);
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



    void movement(const sf::Vector2f& mousePosition);
    void idle(const sf::Vector2f& mousePosition);


    //ability
    bool abilityActive = false;

    bool isDashing = false;
    float dashCooldown = 0.5f;
    sf::Clock dashClock;
    float totalDashDistance = 0;
    float dashDistance = 300;
    void dash(const sf::Vector2f& mousePosition);



    BlastPool blastPool; //blast
    void reset();
    void checkAbility(sf::Mouse::Button button, const sf::Vector2f& mousePos, GridSystem& grid);
    void setAbilityInactive();
};