#pragma once
#include "../header/utility.h"
#include "../header/player/abilities/ability.h"

class Blast : public Ability {
private:
    CircleCollision hitBox;

    float blastSpeed; //how fast it travels
    float reloadSpeed;

public:
    Blast();
    void startPosition(const sf::Vector2f& playerPosition);
    bool isActive(const sf::FloatRect screenBounds) const;

    virtual void activate(const sf::Vector2f& mousePosition, const sf::Vector2f& playerPosition) override;
    
    
    sf::Vector2f move;
    void update(sf::Vector2f move);
    virtual void render(sf::RenderWindow& window) const override;
};

class BlastPool {
private:
    size_t totalBlasts;
    size_t currentNumBlasts;
    std::vector<std::shared_ptr<Blast>> allBlasts;
    std::vector<std::shared_ptr<Blast>> activeBlasts;

    bool wasMousePressed;
public:
    BlastPool(size_t totalBlasts);
    void currentBlasts(const sf::Vector2f& mousePosition, const sf::Vector2f& playerPosition);
    void update();
    void render(sf::RenderWindow& window) const;
    void resetBlasts(const sf::FloatRect screenBounds);
};