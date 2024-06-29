#pragma once
#include "utility.h"
#include "animation.h"

class Player {
private:
    //variables for player rendering
    sf::Texture player_texture; 
    Animation player_animation; 

    //variables for player movement
    const float battleSpeed;
    const float kingdomSpeed; 
    sf::Vector2f movement;
    bool isMoving;
    bool facingRight;
    
public:
    sf::Sprite player_sprite;

    //constructor
    Player(); 

    //functions
    void playerMovement();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
};