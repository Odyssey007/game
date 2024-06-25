#include "../header/player.h"

Player::Player()
    // Initializing all variables from player in the order they are declared
    : frameRectangle(0, 0, 120, 120), // Setting rectangle dimensions
      frameDuration(0.2f), // Duration of each frame in seconds
      frameNumber(0),
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

void Player::battleMovement(float deltaTime) {
    isMoving = false; // Initially set to false

    sf::Vector2f movement(0.0f, 0.0f);

    // Capture keyboard input for movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        movement.y -= battleSpeed * deltaTime;
        isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        movement.y += battleSpeed * deltaTime;
        isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        if (facingRight) {
            facingRight = false;
            player_sprite.setScale(-1.f, 1.f);
        }
        movement.x -= battleSpeed * deltaTime;
        isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        if (!facingRight) {
            facingRight = true;
            player_sprite.setScale(1.f, 1.f);
        }
        movement.x += battleSpeed * deltaTime;
        isMoving = true;
    }
    // Normalize the movement vector if moving diagonally
    if (isMoving && movement.x != 0.0f && movement.y != 0.0f) {
        movement /= std::sqrt(2.0f); // Divide by the square root of 2
    }
    // Update the player position if moving
    if (isMoving) {
        player_sprite.move(movement);
    }
}

void Player::battleMovement_animation() {
    if (isMoving && animationClock.getElapsedTime().asSeconds() >= frameDuration) {
        frameNumber = (frameNumber + 1) % totalFrames; // Cycle through frames
        frameRectangle.left = frameNumber * 120; // Update the left position of the frame
        player_sprite.setTextureRect(frameRectangle);
        animationClock.restart(); // Reset the clock after updating the frame
    }
}
