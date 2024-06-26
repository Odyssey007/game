#pragma once
#include "utility.h"

class Enemy {
protected:
    std::map<std::string, sf::Texture> enemyTextures;
    //
    sf::FloatRect spriteBounds;

    float movementSpeed;
    std::vector<sf::Vector2f> directions;
    sf::Vector2f bestDirection;
    
    void loadTexture(const std::string& name, const std::string& filePath);
    void generateDirections(int numDirections=16);
    //
    virtual void attacks(float attackRange) = 0;
public:
    Enemy();
    virtual ~Enemy() {};

    sf::Sprite enemySprite;
    virtual void maleeMovement(const sf::Vector2f& target); 
};