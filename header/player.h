#include <SFML/Graphics.hpp>

class Player {
private:
    sf::Sprite player_sprite;
    sf::Texture player_texture;
    float moveSpeed = 200.0f; //pixels per second
public:
    Player();
    Player(float x, float y);
    ~Player();
};