#pragma once
#include "../header/utility.h"
#include "../header/battle/player/abilities/ability.h"
#include "../header/battle/gridSystem.h"

class Blast : public Ability {
private:
    CircleCollision hitBox;
    sf::Vector2f move;
    float blastSpeed;
    sf::Vector2u debuff; //x=hp | y=others
public:
    Blast();
    void startPosition(const sf::Vector2f& playerPosition, const sf::Vector2f& mousePosition);
    void isActive(const sf::FloatRect screenBounds);
    virtual void activate(const sf::Vector2f& mousePosition, const sf::Vector2f& playerPosition) override;
    void update();
    //ABILITY
    virtual sf::Vector2u hitEnemy() override; //returns dmg
    //ENTITY
    virtual sf::FloatRect getBounds() const override;
};

class BlastPool {
private:
    size_t totalBlasts;
    std::vector<std::unique_ptr<Blast>> allBlasts;
    std::vector<std::unique_ptr<Blast>> activeBlasts;
    sf::Clock fireCooldown;
public:
    BlastPool(size_t totalBlasts);
    bool spawnBlast(const sf::Vector2f& mousePos, const sf::Vector2f& playerPos, GridSystem& grid);
    void update(const sf::FloatRect screenBounds);
    void reset();
    void render(sf::RenderWindow& window) const;
};