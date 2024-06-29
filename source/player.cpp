#include "../header/player.h"

Player::Player() 
    :battleSpeed(300.0f),
     kingdomSpeed(300.0f),
     isMoving(false),
     facingRight(true)
{
    if (!player_texture.loadFromFile("assets/playerSheet.png")) {
        throw std::runtime_error("Failed to load player texture");
    }
    player_animation = Animation(&player_texture, {4, 2}, 0.18f);
    player_sprite.setTexture(player_texture);
    player_sprite.setTextureRect(player_animation.uvRect);
    player_sprite.setOrigin(player_animation.uvRect.width / 2.0f, player_animation.uvRect.height / 2.0f); // Set origin to bottom center
    player_sprite.setPosition(650, 500);
}

void Player::playerMovement() {
    //initializing variables
    isMoving = false;
    movement = sf::Vector2f (0.0f, 0.0f); 
    player_sprite.setTextureRect(player_animation.uvRect);  

    //Capture keyboard input for movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) moveUp();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) moveDown(); 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) moveLeft();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) moveRight();

    //Update the player position if moving
    if (isMoving) {
        movement = normalize(movement);        
        player_sprite.move(movement * battleSpeed * DeltaTime::getInstance()->getDeltaTime());
    }
    else{
        player_animation.editScale = true; 
        player_animation.scaleNum = sf::Vector2f(0.93f, 0.93f);
        player_animation.animationUpdate(0, facingRight, player_sprite);
    }
}

void Player::moveUp() {
    movement.y -= battleSpeed * DeltaTime::getInstance()->getDeltaTime();
    player_animation.animationUpdate(1, facingRight, player_sprite);
    isMoving = true;
}

void Player::moveDown() {
    movement.y += battleSpeed * DeltaTime::getInstance()->getDeltaTime(); 
    player_animation.animationUpdate(1, facingRight, player_sprite);
    isMoving = true;
}

void Player::moveLeft() {
    if (facingRight) facingRight = false;
    player_animation.animationUpdate(1, facingRight, player_sprite);
    movement.x -= battleSpeed * DeltaTime::getInstance()->getDeltaTime();
    isMoving = true;
}

void Player::moveRight() {
    if (!facingRight) facingRight = true;
    movement.x += battleSpeed * DeltaTime::getInstance()->getDeltaTime();
    player_animation.animationUpdate(1, facingRight, player_sprite);
    isMoving = true;
}

