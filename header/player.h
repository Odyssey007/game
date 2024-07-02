#pragma once
#include "utility.h"
#include "animation.h"
#include "collision.h"
#include "slime.h"

class Player {
private:
    //variables for player rendering
    sf::Texture player_texture; 

    Animation player_animation; 

    //variables for player movement
    const float battleSpeed;
    const float kingdomSpeed; 
    bool facingRight;
    bool isMoving;
public:
    sf::Sprite player_sprite; 
    sf::Vector2f movement;

    //constructor
    Player(); 

    //functions
    void playerMovement();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
   
    BoxCollision hitBox; 
    //sf::VertexArray slash; 

    float player_health = 100.0f;
    void handleCollision(Slime& s1);
};

class Sword {
    private: 
        sf::Texture swordTexture;

        Animation swordAnimation;
    public:
        sf::Sprite swordSprite;

        bool facingRight; 
        //constructor
        Sword(); 
        void updateSword(sf::Vector2f playerPosition); 
        //void pointSword(const sf::Vector2i& mousePosition);
};