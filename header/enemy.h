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
    //hitbox
    sf::IntRect bounds;
    //functions
    void loadTexture(const std::string& name, const std::string& filePath); //load textures
    void generateDirections(int numDirections=16); //movement
    virtual void meleeMovement(const sf::Vector2f& target); //melee movement
    //!virtual void spawn() = 0;
public:
    //constructor
    Enemy();
    virtual ~Enemy() {};
    //functions
    virtual void attacks() = 0;
    virtual void initialPosition(const sf::Vector2u& resolution) override;
    virtual void handleCollisions(Entity& other) override;
};