#pragma once
#include "../header/utility.h"
#include "../header/battle/player/abilities/ability.h"
#include "../header/battle/gridSystem.h"

class Blast : public Ability {
private:
    CircleCollision hitBox;

    float blastSpeed; //how fast it travels
    float reloadSpeed;

public:
    sf::Vector2f previousPosition = sf::Vector2f(0.0f, 0.0f);
    Blast();
    void startPosition(const sf::Vector2f& playerPosition);
    void isActive(const sf::FloatRect screenBounds);

    virtual sf::Vector2f hitEnemy() override;
    virtual void kill() override;

    virtual sf::FloatRect getBounds() const override;
    virtual void activate(const sf::Vector2f& mousePosition, const sf::Vector2f& playerPosition) override;
    
    sf::Vector2f move;
    void update(sf::Vector2f move);
    virtual void render(sf::RenderWindow& window) const override;
};

class BlastPool {
private:
    size_t totalBlasts;
    size_t currentNumBlasts;
    std::vector<std::unique_ptr<Blast>> allBlasts;
    std::vector<std::unique_ptr<Blast>> activeBlasts;
public:
    sf::Clock fireCooldown;
    bool fired = false;

    BlastPool(size_t totalBlasts);
    void currentBlasts(const sf::Vector2f& mousePosition, const sf::Vector2f& playerPosition, GridSystem& grid);
    void update(const sf::FloatRect screenBounds);
    void render(sf::RenderWindow& window) const;
    void resetBlasts();
};