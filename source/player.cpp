#include "../header/player.h"

Player::Player() :
    //animation
    animationSheetDim(sf::Vector2u(4, 2)), frameDuration(0.18),
    //player stats
    health(100.0f), battleSpeed(300.0f), kingdomSpeed(300.0f),
    //player bounds
    bounds(sf::IntRect(30.0f, 35.0f, 32.0f, 75.0f)),
    //movement
    moveDistance(sf::Vector2f(0.0f, 0.0f)), isMoving(false), facingRight(true)
{
    //preliminaries
    entityType = PLAYER; collisionType = AABB;
    texture.loadFromFile("assets/playerSheet1.png");
    sprite.setTexture(texture);
    animation = Animation(&texture, animationSheetDim, frameDuration);
    sprite.setTextureRect(animation.uvRect);
    //hit box and bounds for player sprite
    hitBox.updateSize(bounds);
    //set origin and position
    initialPosition();
    sprite.setOrigin(sf::Vector2f((bounds.left + bounds.width/2.0f), (bounds.top + bounds.height/2.0f)));
}

void Player::update() {
    //reset each after each movement
    isMoving = false;
    moveDistance = sf::Vector2f (0.0f, 0.0f); 
    
    //Capture keyboard input for movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) moveUp();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) moveDown(); 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) moveLeft();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) moveRight();

    //Update the player position if moving
    if (isMoving) {
        moveDistance = normalize(moveDistance);        
        sprite.move(moveDistance * battleSpeed * DeltaTime::getInstance()->getDeltaTime());
    }
    else{
        //player idle animation
        animation.editScale = true; 
        animation.animationUpdate(0, facingRight, sprite, {0.93f, 0.93f});
    }
    //follow the player position as the hit box
    hitBox.followEntity(sprite.getPosition());
}

//cases for each movement type
void Player::moveUp() {
    moveDistance.y -= battleSpeed * DeltaTime::getInstance()->getDeltaTime();
    animation.animationUpdate(1, facingRight, sprite, {1.0f, 1.0f});
    isMoving = true;
}

void Player::moveDown() {
    moveDistance.y += battleSpeed * DeltaTime::getInstance()->getDeltaTime(); 
    animation.animationUpdate(1, facingRight, sprite, {1.0f, 1.0f});
    isMoving = true;
}

void Player::moveLeft() {
    if (facingRight) facingRight = false;
    moveDistance.x -= battleSpeed * DeltaTime::getInstance()->getDeltaTime();
    animation.animationUpdate(1, facingRight, sprite, {1.0f, 1.0f});
    isMoving = true;
}

void Player::moveRight() {
    if (!facingRight) facingRight = true;
    moveDistance.x += battleSpeed * DeltaTime::getInstance()->getDeltaTime();
    animation.animationUpdate(1, facingRight, sprite, {1.0f, 1.0f});
    isMoving = true;
}

//sets the inital positions
void Player::initialPosition() {
    sf::Vector2f startPos = sf::Vector2f(650.0f, 500.0f); 
    sprite.setPosition(startPos);
}

//returns hit box body 
sf::Shape& Player::getShape() {
    return hitBox.body;
}

float Player::getHealth() {
    return health;
}

void Player::takeDebuffs(float hpHit, float speedHit) {
    health -= hpHit;
    battleSpeed -= speedHit;  
}

//renders player && player-related render
void Player::render(sf::RenderWindow& window) {
    window.draw(sprite);
    window.draw(hitBox.body);
}

size_t Player::getState() {
    return 1;
}

//handles what should player do if they collide with other entity in the game
void Player::handleCollisions(Entity& other) {
    EntityType otherEntity = other.entityType;
    if (otherEntity == ENEMY) {
        handleEnemyCollisions(other);
    } else if (otherEntity == OBSTACLE) {
        handleObjectCollisions(other);
    }
}

void Player::handleObjectCollisions(Entity& object) {
    return;
}

void Player::handleEnemyCollisions(Entity& enemy) {
    if (canAttack(enemy)) {
        switch (enemy.enemyType) {
            case SLIME:
                Slime::playerContact(*this, enemy);
        }
        enemyCooldown[&enemy].restart();
    }
}

//stores each enemy cooldown for attacking buffer
bool Player::canAttack(Entity& enemy) {
    auto it = enemyCooldown.find(&enemy);
    if (it == enemyCooldown.end()) {
        enemyCooldown[&enemy].restart();
        return true;
    }
    return it->second.getElapsedTime() >= sf::seconds(1);
}

//--------------------------------------------------

//function for Sword class
Sword::Sword() {
    //preliminaries
    texture.loadFromFile("assets/sword.png");
    sprite.setTexture(texture);
    animation = Animation(&texture, {1, 1}, 0.18f);
    sprite.setTextureRect(animation.uvRect);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    facingRight = true;
}

void Sword::updateSword(sf::Vector2f playerPosition) {
    animation.animationUpdate(0, facingRight, sprite, {1.0f, 1.0f}); 
    sprite.setPosition(playerPosition.x + 20, playerPosition.y); 
}