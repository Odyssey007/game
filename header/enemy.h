#pragma once
#include "utility.h"

class Enemy {
private:
    sf::Texture slime_texture;
    sf::FloatRect spriteBounds;
    //for movement
    float movementSpeed;
    std::vector<sf::Vector2f> directions;
    sf::Vector2f bestDirection;
    //for attack
    float attackBuffer ;
    bool attacking;
    bool recovering;
    float attackDistance;
    float totalDistanceAttack;

    void generateDirections(int numDirection=16);
    void doAttack(float deltaTime);
public:
    sf::Sprite slime_sprite;
    //idle action || attack checker
    void movement(const sf::Vector2f& target, float deltaTime);
    Enemy();
};