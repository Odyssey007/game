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
    moveDistance(sf::Vector2f(0.0f, 0.0f)), isMoving(false), facingRight(true)
{
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

    //todo
    abilityPools.push_back(std::make_unique<BlastPool>(100));
    //abilities
    // abilities.push_back(std::make_unique<Dash>());
}




void Player::update(const sf::Vector2f& mousePosition, const sf::FloatRect& screenBounds) {
    movement(mousePosition);
    


    //ability    
    for (auto& abilityPool : abilityPools) {
        abilityPool->update(screenBounds);
    }

    dash(mousePosition);

    // std::cout << abilityActive << std::endl;
    // for (auto& ability : abilities) {
    //     ability->activate(mousePosition, hitBox.getPosition());
    // }
}

void Player::updateAbilities(sf::Mouse::Button button, const sf::Vector2f& mousePos, GridSystem& grid) {
    for (auto& abilityPool : abilityPools) {
        if (button == sf::Mouse::Left) {
            abilityActive = abilityPool->spawnProjectile(mousePos, getPosition(), grid);
        }
    }
}

void Player::dash(const sf::Vector2f& mousePos) {
    if (!needDash) {
        return;
    }

    // Charging phase
    if (!dashing) {
        chargeTimer -= DeltaTime::getInstance()->getDeltaTime();
        if (chargeTimer <= 0) {
            dashing = true;  // Start dashing
        } else {
            return;
        }
    }

    

    if (dashing && hitWall) {
        dashDirection = sf::Vector2f(0,0);
        hitWall = false;
    }

    // Dashing phase
    if (dashing) {        
        dashDirection = normalize(dashDirection);
        if (totalLeapDistance < leapDistance) {
            float moveFrame = 5.5f * battleSpeed * DeltaTime::getInstance()->getDeltaTime();
            moveDistance = dashDirection * moveFrame;
            totalLeapDistance += magnitude(moveDistance);
        } else {
            // Dash is finished
            moveDistance = sf::Vector2f(0,0);
            totalLeapDistance = 0.0f;
            needDash = false;
            dashing = false;
            chargeTimer = 0.35f;  // Reset charge timer
        }
    }
}

void Player::updateAbilities(sf::Keyboard::Key key, const sf::Vector2f& mousePos, GridSystem& grid) {
    if (key == sf::Keyboard::Space && !needDash) {
        needDash = true;
        abilityActive = true;
        dashDirection = mousePos - getPosition();
    }
}

void Player::setAbilityInactive() {
    abilityActive = false;
}

void Player::cleanUpAbilities() {
    for (auto& abilityPool : abilityPools) {
        abilityPool->cleanUp();
    }
}

//hits wall->hitWall=true ... abilityActive=true -> both true thus 0
void Player::applyMovement() {
    if (dashing) {
        sprite.move(moveDistance);
        hitBox.followEntity(sprite.getPosition());
        return;
    }

    if (moveDistance != sf::Vector2f(0.0f, 0.0f)) {
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
        animation.update(sprite, 1, facingRight, {1.0f, 1.0f});//moving animation
    } else {
        idle(mousePosition);
    }
}

void Player::idle(const sf::Vector2f& mousePosition) {
    if (mousePosition.x >= this->getPosition().x) { //right side
        facingRight = true;
    } else {
        facingRight = false;
    }
    animation.update(sprite, 0, facingRight, {0.93f, 0.93f});
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
    if (otherEntity == BLAST) return;
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

void Player::checkLevelUp(float exp) {
    this->exp += exp;
    if (this->exp >= expRequired) {
        level++;
        this->exp -= expRequired;
        expRequired = 100*std::pow(level-1, 1.5);
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
    window.draw(hitBox.body);

    for (auto& abilityPool : abilityPools) {
        abilityPool->render(window);
    }
    // window.draw(hitBox.body);
    // for (auto& ability : abilities) {
    //     ability->render(window);
    // }
}

//x = hp | y = ms
void Player::takeDebuffs(const sf::Vector2u& debuff) {
    health -= debuff.x;
    battleSpeed -= debuff.y; //!will not work
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