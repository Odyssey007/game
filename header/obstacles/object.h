#pragma once
#include "../header/utility.h"
#include "../header/entity.h"
#include "../header/collision.h"
#include "../header/entity.h"

//obstacleType: 0 - non-dmg | 1 - dmg

class Object {
private:
    //texture
    sf::Texture texture;
    sf::Sprite sprite;
    //hitbox
    BoxCollision hitBox;
    sf::FloatRect bounds;
    sf::FloatRect currentBounds;
    //functions
    void resolveBoxCollision(sf::Vector2f& velocity, const sf::FloatRect& entityBounds);
    void resolveCircleCollision(sf::Vector2f& velocity, const sf::FloatRect& entityBounds);
public:
    sf::RectangleShape obstacle; //?temporary

    Object();
    //functions
    void initialPosition(const sf::View& view);
    void render(sf::RenderWindow& window);
    //sf::FloatRect getGlobalBounds();
    void handleCollision(Entity& entity);
};