#include <SFML/Graphics.hpp>

class Player {
private:
    sf::Texture player_texture;
    float moveSpeed = 200.0f; //pixels per second
public:
    sf::Sprite player_sprite;
    Player();
    ~Player();
};