#include "../header/player/weapon.h"

Sword::Sword() {
    //preliminaries
    texture.loadFromFile("assets/sword.png");
    sprite.setTexture(texture);
    animation = Animation(&texture, {1, 1}, 0.18f);
    sprite.setTextureRect(animation.uvRect);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    facingRight = true;
}

void Sword::updateSword(sf::Vector2f playerPosition) {
    animation.animationUpdate(0, facingRight, sprite, {1.0f, 1.0f}); 
    sprite.setPosition(playerPosition.x + 20, playerPosition.y); 
}