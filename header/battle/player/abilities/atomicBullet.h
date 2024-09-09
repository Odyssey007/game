#pragma once 
#include "../header/utility.h"
#include "../header/battle/player/abilities/ability.h"

class AtomicBullet : public Ability {
private:
    CircleCollision hitBox;
    sf::Vector2f move;
    float speed;
    sf::Vector2u debuff;
    //
    bool diedGoingOut;
public:
    bool isGoneOut() const;
    AtomicBullet();
    void startPosition(const sf::Vector2f& playerPos, const sf::Vector2f& mousePos);
    void isActive(const sf::FloatRect screenBounds);
    void update();
    //ABILITY
    virtual sf::Vector2u hitEnemy() override; //returns dmg
    virtual void activate(const sf::Vector2f& mousePos, const sf::Vector2f& playerPos) override;
    //ENTITY
    virtual sf::FloatRect getBounds() const override;
};

class AtomicResidue : public Ability {
private:
    float upTime; //how long it stays alive 
    sf::Vector2u debuff;
    CircleCollision hitBox;
    //scaling
    float curScale;
    float targetScale;
    float elapsedTime;
    float scaleDuration;
    sf::FloatRect calcBounds(float scale);
    bool upScale; //up-scale
    void enlargeSize();
    bool downScale; //down-scale
    void reduceSize();
    //reset
    void setProperties();
public:
    AtomicResidue();
    void startPosition(const sf::Vector2f& bulletPos);
    void isActive();
    void update();
    //ABILITY
    virtual sf::Vector2u hitEnemy() override;
    //ENTITY
    virtual sf::FloatRect getBounds() const override;
};

class AtomicBulletPool : public AbilityPool {
private:
    std::vector<std::unique_ptr<AtomicBullet>> allBullets;
    std::vector<std::unique_ptr<AtomicBullet>> activeBullets;
    //residue
    std::vector<std::unique_ptr<AtomicResidue>> allResidue;
    std::vector<std::unique_ptr<AtomicResidue>> activeResidue; 
public:
    AtomicBulletPool(size_t totalBullets);
    virtual void cleanUp(GridSystem& grid) override;
    virtual void update(const sf::FloatRect screenBounds) override;
    virtual bool spawnProjectile(const sf::Vector2f& target, const sf::Vector2f& playerPos, GridSystem& grid) override;
    virtual void render(sf::RenderWindow& window) const override;
    //residue
    void spawnResidue(const sf::Vector2f& bulletPos, GridSystem& grid);
};