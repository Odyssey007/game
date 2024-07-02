#pragma once
#include "animation.h"
#include "player.h"
#include "collision.h"
#include "utility.h"

class Ability {
    private: 
        sf::Texture slashTexture;

        Animation slashAnimation; 
        Player player;
    public:
        sf::Sprite slashSprite;

        bool slashVisible; 
        bool facingRight;
        float slashAngle;
        float slashTime; 

        SlashShape hitBoxSlash; 

        //constructor
        Ability(); 

        void mouseClick(const sf::Vector2i& mousePosition, sf::Vector2f playerPosition);
        void slashSpriteRotation(float angle, sf::Vector2f position); 
        void updateSlashTime(); 
};