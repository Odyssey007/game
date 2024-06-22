#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class Player {
private:
    sf::Texture player_texture;
public:
    sf::Vector2f mousePosition;
    sf::Sprite player_sprite;
    float moveSpeed = 300.0f; //pixels per second
    bool isMoving; //flag to check movement
    //constructor
    Player(); 
    //functions
    void movement(sf::Vector2f targetPosition);
    float length(const sf::Vector2f& vector); 
};