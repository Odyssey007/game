#pragma once
#include "utility.h"
#include "entity.h"
#include "animation.h"

class Enemy : public Entity {
protected:
    //texture
    std::map<std::string, sf::Texture> textures;
    sf::Sprite sprite;
    //animation
    Animation animation;
    sf::Vector2u animationSheetDim;
    float frameDuration;
    //stats
    float health;
    float movementSpeed;
    float baseDamage;
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
    //ENTITY fetchers
    virtual const sf::Vector2f& getVelocity() override;
    //ENTITY setters
    virtual void setInitialPosition(const sf::Vector2u& resolution) override;
    virtual void setVelocity(const sf::Vector2f& velocity) override;
    //ENTITY functions 
    virtual void handleCollision(Entity& entity) override;



    virtual void applyMovement() override;
};