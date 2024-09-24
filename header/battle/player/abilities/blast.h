#pragma once
#include "../header/utility.h"
#include "../header/battle/player/abilities/ability.h"

class Blast : public Ability {
private:
    CircleCollision hitBox;
    sf::Vector2f move;
    float blastSpeed;
    sf::Vector2f debuff; //x=hp | y=others
public:
    Blast();
    void startPosition(const sf::Vector2f& playerPosition, const sf::Vector2f& mousePosition);
    void isActive(const sf::FloatRect screenBounds);
    void update();
    //ABILITY
    virtual sf::Vector2f hitEnemy() override; //returns dmg
    virtual void activate(const sf::Vector2f& mousePosition, const sf::Vector2f& playerPosition) override;
    //ENTITY
    virtual sf::FloatRect getBounds() const override;
};

class BlastPool : public AbilityPool {
private:
    std::vector<std::unique_ptr<Blast>> allBlasts;
    std::vector<std::unique_ptr<Blast>> activeBlasts;
public:
    BlastPool(size_t totalBlasts);
    virtual void cleanUp() override;
    virtual void update(const sf::FloatRect screenBounds) override;
    virtual bool spawnProjectile(const sf::Vector2f& mousePos, 
                                 const sf::Vector2f& playerPos, GridSystem& grid) override;
    virtual void render(sf::RenderWindow& window) const override;
};