#include "../header/battle/player/player.h"

Player::Player() :
    //animation
    animationSheetDim(sf::Vector2u(4, 2)), frameDuration(0.18),
    //player stats
    healthMax(100), health(100), battleSpeed(300.0f), kingdomSpeed(300.0f),
    exp(0), expRequired(1), level(1),
    //player bounds
    bounds(sf::FloatRect(50, 30, 30, 80)),
    //movement
    moveDistance(sf::Vector2f(0.0f, 0.0f)), isMoving(false), facingRight(true), direction(IDLE),
    //blast
    blastPool(100)
{
    hitWall = false; abilityActive = false; numAttacked = 0;
    //preliminaries
    entityType = PLAYER; collisionType = BOX;
    texture.loadFromFile("assets/playerSheet.png");
    sprite.setTexture(texture);
    animation = Animation(texture, animationSheetDim, frameDuration);
    sprite.setTextureRect(animation.uvRect);
    //hit box and bounds for player sprite
    hitBox.updateSize(bounds);
    //set origin
    sprite.setOrigin(sf::Vector2f((bounds.left + bounds.width/2.0f), (bounds.top + bounds.height/2.0f)));

    //ability pools
    abilityPools.push_back(std::make_unique<AtomicBulletPool>(100));
    //abilities
}

void Player::extraSetUp(GridSystem& grid) {
    abilities.push_back(std::make_unique<PiercingShotManager>(grid));
    abilities.push_back(std::make_unique<EnergyBarrier>(grid));
}

void Player::findNearestEnemy(const Entity& enemy) {
    sf::Vector2f toEnemy = enemy.getPosition() - getPosition();
    float length = magnitude(toEnemy);

    if (length <= closest) {
        closest = length;
        closestNeighbor = &enemy;
    }
}

void Player::tempSol() {
    if (closestNeighbor && !closestNeighbor->isAlive()) {
        closestNeighbor = nullptr;
    }
}

void Player::update(const sf::Vector2f& mousePosition, const sf::FloatRect& screenBounds, GridSystem& grid) {    
    movement(mousePosition);

    //----abilities
    sf::Vector2f send = sf::Vector2f(0.0f, 0.0f);
    if (closestNeighbor) {
        send = closestNeighbor->getPosition();    
    } else {
        send = sf::Vector2f(0.0f, 0.0f);
        closest = std::numeric_limits<float>::max();
    }

    dash.update(hitWall, moveDistance); //basic
    blastPool.update(screenBounds); //basic

    // return; //!

    //ability pools
    for (auto& abilityPool : abilityPools) {
        abilityPool->spawnProjectile(send, getPosition(), grid);
        abilityPool->update(screenBounds);
    }
    //ability
    for (auto& ability : abilities) {
        ability->activate(send, getPosition());
        ability->activate(getPosition(), facingRight, isMoving);
        //
        ability->update(send, getPosition(), facingRight);
        ability->update(numAttacked);
    }
}

//for mouse buttons
void Player::updateAbilities(sf::Mouse::Button button, const sf::Vector2f& mousePos, GridSystem& grid) {
    if (button == sf::Mouse::Left) {
       abilityActive = blastPool.spawnProjectile(mousePos, getPosition(), grid);
    }
}

//for keyboard buttons
void Player::updateAbilities(sf::Keyboard::Key key, const sf::Vector2f& mousePos, GridSystem& grid) {
    if (key == sf::Keyboard::Space) {
        sf::Vector2f dashDir(0.0f, 0.0f);
        switch (direction) {
            case IDLE:
                dashDir = mousePos - getPosition();
                if (magnitude(dashDir) > 0) dashDir = normalize(dashDir);
                break;
            case UP:
                dashDir = sf::Vector2f(0.0f, -1.0f);
                break;
            case DOWN:
                dashDir = sf::Vector2f(0.0f, 1.0f);
                break;
            case LEFT:
                dashDir = sf::Vector2f(-1.0f, 0.0f);
                break;
            case RIGHT:
                dashDir = sf::Vector2f(1.0f, 0.0f);
                break;
        }
        abilityActive = dash.activate(dashDir, getPosition());
    }
}
//!SOMETIMES WHEN FIRING YOU GO IDLE AND IDLE REGISTERS HERE AS WELL; MAKING IT USE MOUSE INSTEAD OF DIR

void Player::cleanUpAbilities(GridSystem& grid) {
    for (auto& abilityPool : abilityPools) {
        abilityPool->cleanUp(grid);
    }
    blastPool.cleanUp();
}
//!not used
bool Player::getAbilityStatus() const {
    return abilityActive;
}

void Player::setAbilityInactive() {
    abilityActive = false;
}

void Player::applyMovement() {
    if (moveDistance != sf::Vector2f(0.0f, 0.0f)) {
        //for dash
        if (dash.getIsDashing()) {
            sprite.move(moveDistance);
            hitBox.followEntity(sprite.getPosition());
            return;
        }
        //normal
        moveDistance = normalize(moveDistance);
        moveDistance *= battleSpeed * DeltaTime::getInstance()->getDeltaTime();
        sprite.move(moveDistance);
        hitBox.followEntity(sprite.getPosition());
    }
}

void Player::movement(const sf::Vector2f& mousePosition) {
    if (abilityActive) {
        idle(mousePosition);
        return;
    }
    isMoving = false;
    moveDistance = sf::Vector2f(0.0f, 0.0f);
    //capture keyboard input for movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { //up
        pickFacingDirection(mousePosition);
        moveDistance.y -= battleSpeed * DeltaTime::getInstance()->getDeltaTime();
        isMoving = true; direction = UP;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { //down
        pickFacingDirection(mousePosition);
        moveDistance.y += battleSpeed * DeltaTime::getInstance()->getDeltaTime(); 
        isMoving = true; direction = DOWN;
    } 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { //left
        if (facingRight) facingRight = false;
        moveDistance.x -= battleSpeed * DeltaTime::getInstance()->getDeltaTime();
        isMoving = true; direction = LEFT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { //right
        if (!facingRight) facingRight = true;
        moveDistance.x += battleSpeed * DeltaTime::getInstance()->getDeltaTime();
        isMoving = true; direction = RIGHT;
    };
    //update the player position if moving
    if (isMoving) {
        animation.update(sprite, 1, facingRight, {1.0f, 1.0f});//moving animation
    } else {
        idle(mousePosition);
    }
}

void Player::pickFacingDirection(const sf::Vector2f& mousePos) {
    if (mousePos.x >= this->getPosition().x) { //right side
        facingRight = true;
    } else {
        facingRight = false;
    }
}

void Player::idle(const sf::Vector2f& mousePosition) {
    direction = IDLE;
    pickFacingDirection(mousePosition);
    animation.update(sprite, 0, facingRight, {0.93f, 0.93f});
}

void Player::checkLevelUp(float exp) {
    this->exp += exp;
    if (this->exp >= expRequired) {
        level++;
        this->exp -= expRequired;
        expRequired = 100*std::pow(level-1, 1.5);
    }
}

//x = hp | y = ms
void Player::takeDebuffs(const sf::Vector2u& debuff) {
    health -= debuff.x;
    battleSpeed -= debuff.y; //!will not work
    numAttacked++;
}

//fetchers

uint8_t Player::getLevel() const {
    return level;
}

float Player::getHpPercentage() const {
    if (health < 0) {
        return 0.0f;
    }
    return static_cast<float>(health)/healthMax;
}

float Player::getExpPercentage() const {
    return static_cast<float>(exp)/expRequired;
}

int Player::getCurHealth() const {
    return health;
}

//ENTITY FUNCTIONS

sf::FloatRect Player::getBounds() const {
    return hitBox.getBounds();
}

sf::Vector2f Player::getPosition() const {
    return sprite.getPosition();
} 

const sf::Vector2f& Player::getVelocity() const {
    return moveDistance;
}

void Player::setVelocity(const sf::Vector2f& velocity) {
    moveDistance = velocity;
}

void Player::setInitialPosition(const sf::FloatRect& screenBounds) { 
    sprite.setPosition(screenBounds.width/2, screenBounds.height/2);
    hitBox.followEntity(sf::Vector2f(screenBounds.width/2, screenBounds.height/2));
}

void Player::handleCollision(Entity& other) {
    EntityType otherEntity = other.entityType;
    if (otherEntity == PLAYER || otherEntity == TIMED_ABILITY ||
        otherEntity == COLLISION_ABILITY) return;
    //
    if (otherEntity == ENEMY) {
        handleEnemyCollisions(other);
    } else if (otherEntity == EXP) {
        handleExpCollision(other);
    } else if (otherEntity == OBSTACLE) {
        hitWall = true;
    }
}

void Player::handleExpCollision(Entity& entity) {
    if (entity.isAlive()) {
        Exp* exp = dynamic_cast<Exp*>(&entity);
        this->checkLevelUp(exp->drop());
    }
}

void Player::handleEnemyCollisions(Entity& entity) {
    Enemy* enemy = dynamic_cast<Enemy*>(&entity);
    if (enemy->getAttackTimer() >= enemy->getAttackCooldown()) {
        this->takeDebuffs(enemy->attack());
        enemy->restartAttackTimer();
    }
}

void Player::render(sf::RenderWindow& window) const {
    window.draw(sprite);
    // window.draw(hitBox.body);
}

void Player::renderAbilities(sf::RenderWindow& window) const {
    //basics
    blastPool.render(window);
    //ability pool
    for (auto& abilityPool : abilityPools) {
        abilityPool->render(window);
    }
    //ability
    for (auto& ability : abilities) {
        ability->render(window);
    }
}