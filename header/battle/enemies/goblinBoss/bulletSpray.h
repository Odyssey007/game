#pragma once
#include "../header/battle/enemies/enemyAbility.h"

class BulletSpray : public EnemyAbility {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::FloatRect bounds;
    //
    CircleCollision hitBox;
    //
    sf::Clock test;
    
    float angle = 0.0f;
    float speed = 500.0f;
    float angleIncrement = 0.1f;
    //
    float radius = 50.0f;
    float expansionSpeed = 50.0f;
    //
    void animateMovement();
public:
    BulletSpray();
    void isActive(const sf::FloatRect& screenBounds);
    //
    void update(const sf::Vector2f& bossPos);
    virtual void activate(const sf::Vector2f& spawnPos) override;
    //ENTITY fetchers
    virtual sf::FloatRect getBounds() const override;
    virtual sf::Vector2f getPosition() const override;
    //ENTITY functions 
    virtual void render(sf::RenderWindow& window) const override;
};

class BulletSprayPool {
private:
    uint16_t numShots;
    std::vector<std::unique_ptr<BulletSpray>> shotsPool;
    std::vector<std::unique_ptr<BulletSpray>> activeShots;
    //
    sf::Clock fireCooldown;
    //
    float radius = 100.0f;
    int maxNumPos = 8;
    int curNumPos = 0;
    sf::Vector2f calcStartPos(const sf::Vector2f& bossPos);
public:
    BulletSprayPool();
    void activate(const sf::Vector2f& bossPos, GridSystem& grid);
    void update(const sf::FloatRect& screenBounds, const sf::Vector2f& bossPos);
    void cleanUp();
    void render(sf::RenderWindow& window) const;
};