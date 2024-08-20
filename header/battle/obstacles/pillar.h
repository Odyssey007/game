#pragma once
#include "../header/utility.h"
#include "../header/battle/entity.h"
#include "../header/battle/collision.h"
#include "../header/battle/entity.h"



class Pillar : public Entity {
private:
    //texture
    std::vector<std::unique_ptr<sf::Texture>> textures;
    sf::Sprite sprite;
    //hitbox
    sf::FloatRect bounds;
    sf::FloatRect currentBounds;

    bool alive;

    void selectProperties();
    int typePicker();
    float scalePicker();
    int rotationAngle();
    void loadTexture(const std::string& filePath);

    int spawn();
    sf::Clock timer;
    bool timerRunning = false;
    int pickSide();

    void resolveBoxCollision(sf::Vector2f& velocity, const sf::FloatRect& entityBounds);
    void resolveCircleCollision(sf::Vector2f& velocity, const sf::FloatRect& entityBounds);
public:
    Pillar();
    //functions
    void respawn(const sf::FloatRect& screenBounds);
    virtual bool isAlive() const override; //?idk
    virtual sf::FloatRect getBounds() const override;
    virtual sf::Vector2f getPosition() const override;
    //
    virtual void setInitialPosition(const sf::FloatRect& screenBounds) override;
    //
    virtual void handleCollision(Entity& entity) override;
    virtual void render(sf::RenderWindow& window) const override;
};