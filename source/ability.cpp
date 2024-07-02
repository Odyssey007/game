#include "../header/ability.h"

// function for class Ability
Ability::Ability() : 
    slashVisible(false), facingRight(true), slashAngle(0.0f), slashTime(0.0f)
{
    if (!slashTexture.loadFromFile("assets/slashSheet.png")) {
        throw std::runtime_error("Failed to load player texture");
    }

    slashAnimation = Animation(&slashTexture, {4, 2}, 0.12f);
    slashSprite.setTexture(slashTexture);
    slashSprite.setTextureRect(slashAnimation.uvRect);
    slashSprite.setOrigin(slashSprite.getLocalBounds().width / 2, slashSprite.getLocalBounds().height / 2);
}   

void Ability::mouseClick(const sf::Vector2i& mousePosition, sf::Vector2f playerPosition) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        slashAngle = rotationAngle(playerPosition.x, playerPosition.y, mousePosition.x, mousePosition.y);
        hitBoxSlash.createSlashShape(playerPosition.x, playerPosition.y, 90.0f, 1.2f, slashAngle);
        slashSpriteRotation(slashAngle, playerPosition); 
        slashVisible = true; 
    }
    updateSlashTime(); 
}

void Ability::slashSpriteRotation(float angle, sf::Vector2f position) {
    sf::Vector2f offset(cos(angle) * 70, sin(angle) * 70);
    float angleDegrees = radianToDegrees(angle); 
    slashSprite.setPosition(position + offset);
    slashSprite.setRotation(angleDegrees); 
    slashAnimation.animationUpdate(1, facingRight, slashSprite, {1.0f, 1.0f});
}

void Ability::updateSlashTime() {
    if(slashVisible){
        slashTime += DeltaTime::getInstance()->getDeltaTime(); 
        if(slashTime >= 0.12f){
            slashVisible = false; 
            slashTime = 0.0f; 
        }
    }
}
