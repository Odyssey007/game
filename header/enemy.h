#pragma once
#include <SFML/Graphics.hpp>
//will delete

class Enemy {
private:
    sf::Texture slime_texture;
    float movementSpeed = 200.0f;

    std::vector<sf::Vector2f> directions; 
public:
    sf::Sprite slime_sprite;

    Enemy();

    void generateDirections(int numDirection=16);
    void movement(const sf::Vector2f& target);
    void basicAttack();
};

