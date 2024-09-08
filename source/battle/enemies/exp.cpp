#include "../header/battle/enemies/exp.h"

Exp::Exp() :
    moveSpeed(400), moveDistance(sf::Vector2f(0.0f, 0.0f)), 
    active(false), amount(10.0f)
{
    entityType = EXP; collisionType = BOX;
    //
    texture.loadFromFile("assets/exp_drop.jpg");
    sprite.setTexture(texture);
    //hitbox
    bounds = sf::FloatRect(250.0f, 275.0f, 15.0f, 15.0f);
    hitBox.updateSize(bounds);
    //
    sprite.setScale(0.04f, 0.04f);
    sprite.setOrigin(sf::Vector2f((bounds.left + bounds.width/2.0f), (bounds.top + bounds.height/2.0f)));
    hitBox.followEntity(this->getPosition());
}

void Exp::update(const sf::Vector2f& target) {
    sf::Vector2f rawToTarget = target - this->getPosition();
    sf::Vector2f toTarget = normalize(rawToTarget);

    if (magnitude(rawToTarget) >= 300.0f && active == false) {
        return;
    } else {
        active = true;
    }

    float angle = 30.0f; 
    float radian = angle * 3.14159265f / 180.0f;
    sf::Vector2f adjustedDirection = sf::Vector2f(
        toTarget.x*std::cos(radian) - toTarget.y*std::sin(radian),
        toTarget.x*std::sin(radian) + toTarget.y*std::cos(radian)
    );

    float interpolation = 0.2f;
    moveDistance = moveDistance * (1 - interpolation) + adjustedDirection * interpolation;
    
    float curMoveDist = magnitude(moveDistance);
    if (curMoveDist != 0) {
        moveDistance /= curMoveDist;
    }
    //
    moveDistance *= static_cast<float>(moveSpeed) * DeltaTime::getInstance()->getDeltaTime();
}

float Exp::drop() const {
    return amount;
}

void Exp::spawn(const sf::FloatRect& entityBounds) {
    this->alive = true; this->active = false;
    setInitialPosition(entityBounds);
}

//ENTITY

sf::FloatRect Exp::getBounds() const {
    return sprite.getGlobalBounds(); 
}

sf::Vector2f Exp::getPosition() const {
    return sprite.getPosition();
}

const sf::Vector2f& Exp::getVelocity() const {
    return moveDistance;
}

void Exp::setVelocity(const sf::Vector2f& velocity) {
    moveDistance = velocity;
}

void Exp::setInitialPosition(const sf::FloatRect& entityBounds) {
    float posX = entityBounds.left + entityBounds.width/2.0f;
    float posY = entityBounds.top + entityBounds.height/2.0f;

    sprite.setPosition(posX, posY);
    hitBox.followEntity(this->getPosition());
}

void Exp::applyMovement() {
    sprite.move(moveDistance);
    hitBox.followEntity(this->getPosition());
    moveDistance = sf::Vector2f(0.0f, 0.0f);
}

void Exp::handleCollision(Entity& entity) {
    EntityType otherEntity = entity.entityType;

    if (otherEntity == OBSTACLE || otherEntity == ENEMY || 
        otherEntity == BLAST) return;
    if (otherEntity == PLAYER) alive = false;
}

void Exp::render(sf::RenderWindow& window) const {
    window.draw(sprite);
}