#include "../header/animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u frameDimension, float frameDuration)
{
    //initializing variables
    this->frameDimension = frameDimension; 
    this->frameDuration = frameDuration;
    currentFrame.x = 0; 
    totalTime = 0.0f; 
    //calculating width and height for texture rectangle
    uvRect.width = texture->getSize().x / frameDimension.x; 
    uvRect.height = texture->getSize().y / frameDimension.y;
}

void Animation::animationUpdate(int row, bool faceRight, sf::Sprite& sprite){
    this->row = row; 
    currentFrame.y = row; 
    totalTime += DeltaTime::getInstance()->getDeltaTime(); 

    if(totalTime >= frameDuration) {
        totalTime -= frameDuration;
        currentFrame.x = (currentFrame.x + 1) % frameDimension.x; 
    }

    uvRect.left = currentFrame.x * uvRect.width; 
    uvRect.top = currentFrame.y * uvRect.height; 

    if (faceRight) {
        sprite.setScale(1.0f, 1.0f); 
    } 
    else {
        sprite.setScale(-1.0f, 1.0f);
    }


/*
    if (row == 0) {
        if (faceRight) {
            sprite.setScale(0.95f, 0.95f); 
        } 
        else {
            sprite.setScale(-0.95f, 0.95f);  
        }
    } 
    else {
        if (faceRight) {
            sprite.setScale(1.0f, 1.0f); 
        } 
        else {
            sprite.setScale(-1.0f, 1.0f);
        }
    }
*/
    void animati
}


