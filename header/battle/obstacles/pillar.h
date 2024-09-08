#pragma once
#include "../header/utility.h"
#include "../header/battle/entity.h"
#include "../header/battle/collision.h"
#include "../header/battle/entity.h"
#include "../header/battle/player/abilities/ability.h"

class Pillar : public Entity {
private:
    //texture
    std::vector<std::unique_ptr<sf::Texture>> textures;
    sf::Sprite sprite;
    //hitbox
    sf::FloatRect bounds;
    sf::FloatRect currentBounds;
    //respawn
    sf::Clock timer;
    bool timerRunning = false;
    void respawnPosition(const sf::FloatRect& screenBounds);
    //attribute selectors
    void selectProperties();
    int attributeSelectorI(int first, int second);
    float attributeSelectorF(float first, float second);
    int rotationAngle();
    //handleCollision
    void stopEntities(Entity& entity);
    bool resolveBoxCollision(sf::Vector2f& velocity, const sf::FloatRect& entityBounds);
    bool resolveCircleCollision(sf::Vector2f& velocity, const sf::FloatRect& entityBounds);
    //
    void loadTexture(const std::string& filePath);
public:
    Pillar();
    void respawn(const sf::FloatRect& screenBounds);
    //ENTITY fetchers
    virtual sf::FloatRect getBounds() const override;
    virtual sf::Vector2f getPosition() const override;
    //ENTITY setters
    virtual void setInitialPosition(const sf::FloatRect& screenBounds) override;
    //ENTITY functions
    virtual void handleCollision(Entity& entity) override;
    virtual void render(sf::RenderWindow& window) const override;
};