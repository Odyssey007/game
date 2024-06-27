#include "../header/player.h"

Player::Player()
    // Initializing all variables from player in the order they are declared
    :  // Setting rectangle dimensions
      frameDuration(0.18f), // Duration of each frame in seconds
      frameNumber(0), // makes sure starting with the first sprite frame
      totalFrames(4), // Total number of frames in the animation
      battleSpeed(300.0f), // Pixels per second
      kingdomSpeed(300.0f), // Pixels per second
      isMoving(false), // Spawns the player without moving
      facingRight(true) // Initial direction
{
    if (!player_texture.loadFromFile("assets/playerSheet.png")) {
        throw std::runtime_error("Failed to load player texture");
    }

    player_sprite.setTexture(player_texture);
    player_sprite.setTextureRect(frameRectangle);
    player_sprite.setOrigin(frameRectangle.width / 2.0f, frameRectangle.height / 2.0f); // Set origin to bottom center
    player_sprite.setPosition(650, 500);
}

void Player::playerMovement() {
    //initializing variables
    isMoving = false;
    movement = sf::Vector2f (0.0f, 0.0f); 
    frameRectangle = sf::IntRect (0, 147, 120, 295); 

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
        idle(); 
    }

    playerMovement_animation(); //update player animation
}

void Player::moveUp() {
    movement.y -= battleSpeed * DeltaTime::getInstance()->getDeltaTime();
    isMoving = true;
}

void Player::moveDown() {
    movement.y += battleSpeed * DeltaTime::getInstance()->getDeltaTime(); 
    isMoving = true;
}

void Player::moveLeft() {
    if (facingRight) {
            facingRight = false;
            player_sprite.setScale(-1.f, 1.f);
        }
    movement.x -= battleSpeed * DeltaTime::getInstance()->getDeltaTime();
    isMoving = true;
}

void Player::moveRight() {
    if (!facingRight) {
            facingRight = true;
            player_sprite.setScale(1.f, 1.f);
        }
    movement.x += battleSpeed * DeltaTime::getInstance()->getDeltaTime();
    isMoving = true;
}

void Player::idle() {
    if(!isMoving) {
        frameRectangle = sf::IntRect (0, 0, 75, 148); 
        idleAnimation(); 
    }
}

void Player::playerMovement_animation() {
    if (isMoving && animationClock.getElapsedTime().asSeconds() >= frameDuration) {
        frameNumber = (frameNumber + 1) % totalFrames; // Cycle through frames
        frameRectangle.left = frameNumber * 120; // Update the left position of the frame
        player_sprite.setTextureRect(frameRectangle);
        animationClock.restart(); // Reset the clock after updating the frame
    }
}

void Player::idleAnimation() {
    if(!isMoving && animationClock.getElapsedTime().asSeconds() >= frameDuration) {
        frameNumber = (frameNumber + 1) % 5;
        frameRectangle.left = frameNumber * 86; 
        player_sprite.setTextureRect(frameRectangle);
        animationClock.restart(); 
        frameNumber = frameNumber % 5;
    }
}
