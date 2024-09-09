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
    int getCurHealth() const;
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


    //dash
    bool hitWall = false;


    sf::Vector2f dashDirection;
    bool needDash = false;
    void dash(const sf::Vector2f& mousePos);
    bool dashing = false;
    float chargeTimer = 0.15f;
    float totalLeapDistance = 0.0f;
    float leapDistance = 150.f;

    //ability
    bool abilityActive = false;
    std::vector<std::unique_ptr<Ability>> abilities;
    std::vector<std::unique_ptr<AbilityPool>> abilityPools; 
    void updateAbilities(sf::Keyboard::Key key, const sf::Vector2f& mousePos, GridSystem& grid);
    void updateAbilities(sf::Mouse::Button button, const sf::Vector2f& mousePos, GridSystem& grid);
    void setAbilityInactive();
    void cleanUpAbilities();

    void abilityFactory();
};