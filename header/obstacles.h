#pragma once
#include "utility.h"
#include "entity.h"
#include "collision.h"
#include "entity.h"

//obstacleType: 0 - non-dmg | 1 - dmg

class Object {
private:
    //texture
    
    sf::Texture texture;
    sf::Sprite sprite;
    //hitbox
    BoxCollision hitBox;
    sf::FloatRect bounds;
    //functions
    void handleCollisionBox(Entity& other);
    void handleCollisionCircle(Entity& other);
public:
    sf::RectangleShape obstacle; //?temporary

    Object();
    //functions
    void initialPosition(const sf::Vector2u& position);
    void render(sf::RenderWindow& window);

    sf::FloatRect getGlobalBounds();

    void handleCollision(Entity& entity);
};