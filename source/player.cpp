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
    //player_sprite.setOrigin(player_animation.uvRect.width / 2.0f, player_animation.uvRect.height / 2.0f); // Set origin to bottom center
    player_sprite.setPosition(650, 500);

    sf::IntRect bounds;
    hitbox.body.setPosition(650, 500);

    bounds.width = 32;
    bounds.left = 30;

    bounds.height = 75;
    bounds.top = 35;
    
    hitbox.updateSize(bounds);
    
    sf::Vector2f origin;
    origin.x = bounds.left + bounds.width/2.0f;
    origin.y = bounds.top + bounds.height/2.0f;
    player_sprite.setOrigin(origin);
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
        player_animation.scaleNum = {.93f, .93f};
        player_animation.animationUpdate(0, facingRight, player_sprite, {.93f, .93f});
    }
    hitbox.followEntity(player_sprite.getPosition());
}


void Player::moveUp() {
    movement.y -= battleSpeed * DeltaTime::getInstance()->getDeltaTime();
    player_animation.animationUpdate(1, facingRight, player_sprite, {1.0f, 1.0f});
    isMoving = true;
}

void Player::moveDown() {
    movement.y += battleSpeed * DeltaTime::getInstance()->getDeltaTime(); 
    player_animation.animationUpdate(1, facingRight, player_sprite, {1.0f, 1.0f});
    isMoving = true;
}

void Player::moveLeft() {
    if (facingRight) facingRight = false;
    player_animation.animationUpdate(1, facingRight, player_sprite, {1.0f, 1.0f});
    movement.x -= battleSpeed * DeltaTime::getInstance()->getDeltaTime();
    isMoving = true;
}

void Player::moveRight() {
    if (!facingRight) facingRight = true;
    movement.x += battleSpeed * DeltaTime::getInstance()->getDeltaTime();
    player_animation.animationUpdate(1, facingRight, player_sprite, {1.0f, 1.0f});
    isMoving = true;
}

