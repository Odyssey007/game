#include "player.h"

Player::Player() {
    //!image is not loading as it suppose to
    if (!player_texture.loadFromFile("../assets/player.png")) {
        exit;
    }
    player_sprite.setTexture(player_texture);
}

