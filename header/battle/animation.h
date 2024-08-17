#pragma once 
#include "../header/battle/utility.h"

class Animation {
private: 
    sf::Vector2u frameDimension; // coordinations for rows and columns 
    sf::Vector2u currentFrame; 
    float frameDuration; 
    float totalTime; 
public:
    sf::IntRect uvRect;
    
    //constructors
    Animation();
    Animation(sf::Texture* texture, sf::Vector2u frameDimension, float frameDuration);
    //function 
    void animationUpdate(int row, bool faceRight, sf::Sprite& sprite, sf::Vector2f scaleNum);
};