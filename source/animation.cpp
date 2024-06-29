#include "../header/animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u frameDimension, float frameDuration)
{
    //initializing variables
    this->frameDimension = frameDimension; 
    this->frameDuration = frameDuration;
    currentFrame.x = 0; 
    totalTime = 0.0f; 
    //calculating width and height for texture rectangle
    //uvRect.width = texture->getSize().x / frameDimension.x; 
    //uvRect.height = texture->getSize().y / frameDimension.y;

    uvRect.width = 81;
    uvRect.height = 147;
}

void Animation::animationUpdate(int row){
    currentFrame.y = row; 
    totalTime += DeltaTime::getInstance()->getDeltaTime(); 

    if(totalTime >= frameDuration){
        totalTime -= frameDuration;
        currentFrame.x = (currentFrame.x + 1) % frameDimension.x; 
    }

    uvRect.left = currentFrame.x * uvRect.width; 
    uvRect.top = currentFrame.y * uvRect.height; 
}

void Animation::check_facingRight(bool faceRight){
    
}
