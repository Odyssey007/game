#pragma once
#include "../header/battle/entity.h"
#include "../header/battle/collision.h"

class Exp : public Entity {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    //
    BoxCollision hitBox;
    sf::FloatRect bounds;
    //movement
    int moveSpeed;
    sf::Vector2f moveDistance;
    //
    bool active;
    //
    float amount;
public:
    Exp();
    ~Exp() = default;
    //
    float drop() const;
    void update(const sf::Vector2f& target);
    //ENTITY fetchers
    virtual sf::FloatRect getBounds() const override;
    virtual sf::Vector2f getPosition() const override;
    virtual const sf::Vector2f& getVelocity() const override;
    //ENTITY setters
    virtual void setVelocity(const sf::Vector2f& velocity) override;
    virtual void setInitialPosition(const sf::FloatRect& entityBounds) override;
    //ENTITY fuctions
    virtual void applyMovement() override;
    virtual void handleCollision(Entity& entity) override;
    virtual void render(sf::RenderWindow& window) const override;
};

/*
tier 1: 10% of the EXP required to lvl
tier 2: 25& of the EXP required to lvl 
tier 3: ion know 
*/