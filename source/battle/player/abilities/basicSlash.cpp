#include "../header/battle/player/abilities/basicSlash.h"

// function for class Ability
Slash::Slash() : 
    slashVisible(false), facingRight(true), slashAngle(0.0f), slashTime(0.0f)
{
    sprite.setTexture(*textures["basicSlash"]);
    animation = Animation(*textures["basicSlash"], {4, 2}, 0.12f);
    sprite.setTextureRect(animation.uvRect);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    //default key
    key = sf::Keyboard::Key::Unknown;
    mouseKey = sf::Mouse::Button::Right;
}

void Slash::kill() {
    alive = false;
};

void Slash::activate(const sf::Vector2f& mousePosition, const sf::Vector2f& playerPosition) { 
    if (sf::Mouse::isButtonPressed(mouseKey) || sf::Keyboard::isKeyPressed(key)) {
        slashVisible = true;
        if(slashVisible){
            slashAngle = rotationAngle(playerPosition.x, playerPosition.y, mousePosition.x, mousePosition.y);
            hitBoxSlash.createSlashShape(playerPosition.x, playerPosition.y, 90.0f, 1.2f, slashAngle);
            slashSpriteRotation(slashAngle, playerPosition); 
        }
    }
    updateSlashTime(); 
}

void Slash::slashSpriteRotation(float angle, sf::Vector2f position) {
    sf::Vector2f offset(cos(angle) * 70, sin(angle) * 70);
    float angleDegrees = radianToDegrees(angle); 
    sprite.setPosition(position + offset);
    sprite.setRotation(angleDegrees);
    for (size_t i = 0; i < 4; i++) {
        animation.update(sprite, 1, facingRight, {1.0f, 1.0f});
    }
}

void Slash::updateSlashTime() {
    if(slashVisible){
        slashTime += DeltaTime::getInstance()->getDeltaTime(); 
        if(slashTime >= 0.12f){
            slashVisible = false; 
            slashTime = 0.0f; 
        }
    }
}

void Slash::render(sf::RenderWindow& window) const {
    if(slashVisible) {
        window.draw(sprite);
    }
}