#pragma once
#include "utility.h"
#include "animation.h"
#include "player.h"
#include "collision.h"


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

    void mouseClick(const sf::Vector2f& mousePosition, sf::Vector2f playerPosition);
    void slashSpriteRotation(float angle, sf::Vector2f position); 
    void updateSlashTime(); 
    void render(sf::RenderWindow& window);
};