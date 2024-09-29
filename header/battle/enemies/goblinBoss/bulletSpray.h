#pragma once
#include "../header/battle/enemies/enemyAbility.h"

class BulletSpray : public EnemyAbility {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    //
    sf::FloatRect bounds;
    CircleCollision hitBox;
    //
    float speed;
    sf::Vector2f originPos;
    //
    void animateMovement();
public:
    BulletSpray();
    void update(const sf::Vector2f& bossPos);
    void isActive(const sf::FloatRect& screenBounds);
    void setOriginPos(const sf::Vector2f& originPos); //needed by manager
    //
    virtual void activate(const sf::Vector2f& spawnPos) override;
    virtual sf::Vector2f attack() override;
    //ENTITY fetchers
    virtual sf::FloatRect getBounds() const override;
    virtual sf::Vector2f getPosition() const override;
    //ENTITY functions 
    virtual void handleCollision(Entity& entity) override;
    virtual void render(sf::RenderWindow& window) const override;
};

class BulletSprayPool {
private:
    std::vector<std::unique_ptr<BulletSpray>> shotsPool;
    std::vector<std::unique_ptr<BulletSpray>> activeShots;
    bool alive;
    uint8_t numShots;
    //
    bool shouldCast;
    float abilityCooldown;
    //
    bool isFiring;
    float abilityDuration;
    sf::Clock fireCooldown;
    //
    float angleOffset;
    float angleIncrement;
    uint8_t maxNumPos;
    uint8_t curNumPos;
    float radius;
    //
    sf::Vector2f calcStartPos(const sf::Vector2f& bossPos);
public:
    BulletSprayPool();
    bool isAlive() const;
    bool canCast() const;
    bool cooldown(bool& abilityActive);
    void activate(const sf::Vector2f& bossPos, GridSystem& grid);
    void update(const sf::FloatRect& screenBounds, const sf::Vector2f& bossPos);
    void cleanUp();
    void render(sf::RenderWindow& window) const;
};