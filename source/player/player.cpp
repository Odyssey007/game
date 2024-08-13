#include "../header/player/player.h"

Player::Player() :
    //animation
    animationSheetDim(sf::Vector2u(4, 2)), frameDuration(0.18),
    //player stats
    health(100.0f), battleSpeed(300.0f), kingdomSpeed(300.0f), alive(true),
    //player bounds
    bounds(sf::FloatRect(50, 30, 30, 80)),
    //movement
    moveDistance(sf::Vector2f(0.0f, 0.0f)), isMoving(false), facingRight(true)
{
    //preliminaries
    entityType = PLAYER; collisionType = AABB;
    texture.loadFromFile("assets/playerSheet.png");
    sprite.setTexture(texture);
    animation = Animation(&texture, animationSheetDim, frameDuration);
    sprite.setTextureRect(animation.uvRect);
    //hit box and bounds for player sprite
    hitBox.updateSize(bounds);
    //set origin
    sprite.setOrigin(sf::Vector2f((bounds.left + bounds.width/2.0f), (bounds.top + bounds.height/2.0f)));
    //abilities
    abilities.push_back(std::make_shared<Slash>()); 
}

void Player::dash(const sf::Vector2f& mousePosition) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && dashClock.getElapsedTime().asSeconds() > dashCooldown) {
        isDashing = true;
        dashClock.restart();

        // Calculate move distance
        sf::Vector2f direction = mousePosition - sprite.getPosition();
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
        moveDistance = direction / length;
        totalDashDistance = 0; 
    }

    if (isDashing) {
        if (totalDashDistance < dashDistance) {
            sf::Vector2f move;
            move.x = moveDistance.x * DeltaTime::getInstance()->getDeltaTime() * 200 * 6;
            move.y = moveDistance.y * DeltaTime::getInstance()->getDeltaTime() * 200 * 6;

            sprite.move(move);
            hitBox.followEntity(sprite.getPosition());
            totalDashDistance += magnitude(move);
        } else {
            isDashing = false; 
        }
    }
}


void Player::update(const sf::Vector2f& mousePosition) {
    dash(mousePosition);

    movement();

    for (auto& ability : abilities) {
        ability->activate(mousePosition, hitBox.body.getPosition());
    }
}

void Player::applyMovement() {
    if (moveDistance != sf::Vector2f(0.0f, 0.0f)) {
        moveDistance = normalize(moveDistance);
        moveDistance *= battleSpeed * DeltaTime::getInstance()->getDeltaTime();
        sprite.move(moveDistance);
        hitBox.followEntity(sprite.getPosition());
    }
}

void Player::movement() {
    //reset each after each movement
    isMoving = false;
    moveDistance = sf::Vector2f(0.0f, 0.0f);
    //Capture keyboard input for movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { //up
        moveDistance.y -= battleSpeed * DeltaTime::getInstance()->getDeltaTime();
        isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { //down
        moveDistance.y += battleSpeed * DeltaTime::getInstance()->getDeltaTime(); 
        isMoving = true;
    } 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { //left
        if (facingRight) facingRight = false;
        moveDistance.x -= battleSpeed * DeltaTime::getInstance()->getDeltaTime();
        isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { //right
        if (!facingRight) facingRight = true;
        moveDistance.x += battleSpeed * DeltaTime::getInstance()->getDeltaTime();
        isMoving = true;
    };
    //update the player position if moving
    if (isMoving) {
        animation.animationUpdate(1, facingRight, sprite, {1.0f, 1.0f});//moving animation
    } else {
        animation.animationUpdate(0, facingRight, sprite, {0.93f, 0.93f});//idle animation
    }
}

//ENTITY FUNCTIONS

bool Player::isAlive() const {
    return alive;
}

//is not used
int Player::getState() const {
    return 1;
}

sf::FloatRect Player::getBounds() const {
    return hitBox.body.getGlobalBounds();
}

sf::Vector2f Player::getPosition() const {
    return hitBox.body.getPosition();
} 

const sf::Vector2f& Player::getVelocity() const {
    return moveDistance;
}

void Player::setVelocity(const sf::Vector2f& velocity) {
    moveDistance = velocity;
}

void Player::setInitialPosition(const sf::View& view) { 
    sprite.setPosition(view.getSize().x/2, view.getSize().y/2);
    hitBox.body.setPosition(view.getSize().x/2, view.getSize().y/2);
}

void Player::handleCollision(Entity& other) {
    EntityType otherEntity = other.entityType;
    if (otherEntity == ENEMY) {
        handleEnemyCollisions(other);
    } else if (otherEntity == OBSTACLE) {
        handleObjectCollisions(other);
    }
}

void Player::render(sf::RenderWindow& window) const {
    window.draw(sprite);
    window.draw(hitBox.body);
    for (auto& ability : abilities) {
        ability->render(window);
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

void Player::handleEnemyCollisions(Entity& enemy) {
    if (canAttack(enemy)) {
        switch (enemy.enemyType) {
            case SLIME:
                Slime::playerContact(*this, enemy);
        }
        enemyCooldown[&enemy].restart();
    }
}

void Player::handleObjectCollisions(Entity& object) {
    
}

void Player::takeDebuffs(float hpHit, float speedHit) {
    health -= hpHit;
    battleSpeed -= speedHit;  
}

//fetchers

float Player::getHealth() {
    return health;
}