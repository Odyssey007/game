#include "../header/player.h"

Player::Player() {
    if (!player_texture.loadFromFile("../assets/player4.png")) {
        throw std::runtime_error ("Failed to load player texture");
    }
    player_sprite.setTexture(player_texture);
    player_sprite.setOrigin(player_texture.getSize().x / 2, player_texture.getSize().y);  // Set origin to bottom center
    player_sprite.setPosition(960, 540); 
    isMoving = false;
}

void Player::movement(const sf::Vector2f targetPosition){
    this->mousePosition = targetPosition;
    this->isMoving = true; 
} 

float Player::length(const sf::Vector2f& vector) {
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}