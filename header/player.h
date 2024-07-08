#pragma once
#include "utility.h"
#include "entity.h"
#include "animation.h"
#include "slime.h"

#include "obstacles.h"

enum PlayerAbilities {  };

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
    //hit box
    BoxCollision hitBox;
    sf::FloatRect bounds;
    //player movement
    sf::Vector2f moveDistance;
    bool isMoving;
    bool facingRight;
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    //enemy cooldown
    std::unordered_map<Entity*, sf::Clock> enemyCooldown;
    bool canAttack(Entity& entity);
    //collision handling
    void handleEnemyCollisions(Entity& other);
    void handleObjectCollisions(Entity& other);
public:
    //constructor
    Player(); 
    //fetchers
    float getHealth();
    //functions
    void update();
    void takeDebuffs(float hpHit, float speedHit);
    
    //ENTITY fetchers
    virtual size_t getState() override;
    virtual const sf::Shape& getShape() override;
    virtual const sf::Vector2f& getVelocity() override;
    //ENTITY setters
    virtual void setVelocity(const sf::Vector2f& velocity) override;
    virtual void setInitialPosition(const sf::Vector2u& position) override;
    //ENTITY functions
    virtual void handleCollision(Entity& other) override;
    virtual void render(sf::RenderWindow& window) override;

    virtual void applyMovement() override;
};

//---------------------------------

class Sword {
    private: 
        sf::Texture texture;
        sf::Sprite sprite;
        Animation animation;

        bool facingRight;
    public: 
        //constructor
        Sword();
        //function
        void updateSword(sf::Vector2f playerPosition);
};