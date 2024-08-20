#pragma once
#include "../header/utility.h"
#include "../header/battle/entity.h"
#include "../header/animation.h"
#include "../header/battle/collision.h"

class Enemy : public Entity {
protected:
    //texture
    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> textures;
    sf::Sprite sprite;
    //animation
    Animation animation;
    sf::Vector2u animationSheetDim;
    float frameDuration;
    //stats 
    int health;
    int movementSpeed;
    int baseDamage;
    //atributes 
    EnemyType enemyType;
    int currentAbility;
    bool alive;
    //movement 
    std::vector<sf::Vector2f> directions;
    sf::Vector2f bestDirection;
    sf::Vector2f moveDistance;
    //hitbox
    sf::FloatRect bounds;
    //functions
    void loadTexture(const std::string& name, const std::string& filePath); //load textures
    void generateDirections(int numDirections=32); //movement
    virtual void meleeMovement(const sf::Vector2f& target); //melee movement
    virtual void attacks() = 0; //
public:
    //constructor
    Enemy();
    virtual ~Enemy() = default;
    virtual void update(const sf::Vector2f& target) = 0;
    //ENTITY fetchers
    virtual bool isAlive() const override;
    virtual const sf::Vector2f& getVelocity() const override;
    //ENTITY setters
    virtual void setVelocity(const sf::Vector2f& velocity) override;
    virtual void setInitialPosition(const sf::FloatRect& screenBounds) override;
    //ENTITY functions 
    virtual void applyMovement() override;
    virtual void handleCollision(Entity& entity) override;



    std::vector<Entity*> neighbors;
    std::vector<Entity*> objectNeighbors;

    void boxOverlap(Entity& entity1, Entity& entity2);
    void circleOverlap(Entity& entity1, Entity& entity2);
    void boxCircleOverlap(Entity& box, Entity& circle);
};