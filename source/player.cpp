#include "../header/player.h"

Player::Player() {
    //!image is not loading as it suppose to
    if (!player_texture.loadFromFile("../assets/player.png")) {
        return;
    }
    player_sprite.setTexture(player_texture);
}

Player::~Player() {
//helo
}