#pragma once 
#include "../header/utility.h"

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
    Animation(const sf::Texture& texture, const sf::Vector2u& frameDimension, float frameDuration);
    //function 
    void update(sf::Sprite& sprite, int row, bool faceRight, const sf::Vector2f& scaleNum);
    void resetToFirst(sf::Sprite& sprite, bool faceRight, const sf::Vector2f& scaleNum);
};