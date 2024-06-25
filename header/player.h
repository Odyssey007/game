#include <SFML/Graphics.hpp>
#include <cmath>

class Player {
private:
    sf::Texture player_texture;
public:
    //variables for player movement rendering
    sf::Sprite player_sprite;
    sf::IntRect frameRectangle;

    //variables for player movement animation
    sf::Clock movement_animationClock; 
    float movement_frameDuration;
    int movement_frameNumber; 
    const int movement_totalFrames;

    //variables for player standing animation

    //variables for player movement
    const float battleSpeed;
    const float kingdomSpeed; 
    bool isMoving;
    bool facingRight;

    //constructor
    Player(); 

    //functions
    void battleMovement(float deltaTime);
    void battleMovement_animation();
    float length(const sf::Vector2f& vector); 
};

