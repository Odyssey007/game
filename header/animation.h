#pragma once 
#include "utility.h"

class Animation {
    private: 
        sf::Vector2u frameDimension; // coordinations for rows and columns 
        sf::Vector2u currentFrame; 
        float frameDuration; 
        float totalTime; 
    public: 
        //default constructor
        Animation(){
            frameDimension = {0, 0};
            currentFrame = {0, 0};
            frameDuration = {0.0f}; 
            totalTime = {0.0f};
        }
        //constructor with parameter 
        Animation(sf::Texture* texture, sf::Vector2u frameDimension, float frameDuration);
        sf::IntRect uvRect; 
        void animationUpdate(int row);
        void check_facingRight(bool faceRight); 
};