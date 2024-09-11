#include "../header/battle/player/abilities/piercingShot.h"

PiercingShotManager::PiercingShotManager(GridSystem& grid) : 
    //stat
    fireRange(500.0f), numShots(3),
    //buffer
    timerBeforeStart(0.0f), cooldownBeforeStart(0.5f)
{
    for (size_t i = 0; i < numShots; ++i) {
        shots.emplace_back(std::make_unique<PiercingShot>());
        grid.addEntity(*shots[i]);
    }
}

bool PiercingShotManager::startBuffer() {
    timerBeforeStart += DeltaTime::getInstance()->getDeltaTime();

    if (timerBeforeStart >= cooldownBeforeStart) {
        timerBeforeStart = 0.0f;
        return true;
    }
    return false;
}

//checks when it should be active 
void PiercingShotManager::activate(const sf::Vector2f& target, const sf::Vector2f& playerPos) {
    sf::Vector2f toTarget = target - playerPos;
    float distToTarget = magnitude(toTarget);

    if (distToTarget <= fireRange) { //will activate
        for (size_t i = 0; i < numShots; ++i) {
            if (!shots[i]->active && startBuffer()) {
                shots[i]->active = true;
                break; 
            }
        }
    } else { //wont activate && if active will revert
        for (size_t i = 0; i < numShots; ++i) {
            if (shots[i]->active) {
                shots[i]->revert = true;
            }
        }  
    }
}

void PiercingShotManager::update(const sf::Vector2f& target, const sf::Vector2f& playerPos, bool playerFacingRight) {
    for (size_t i = 0; i < numShots; ++i) {
        if (shots[i]->active) { //active
            //buffers after hitting
            if (shots[i]->hit) {
                shots[i]->afterHitBuffer();
                continue;
            }
            //
            if (shots[i]->revert) {
                sf::Vector2f restPos = shots[i]->calcStartPos(playerPos, playerFacingRight, i);
                shots[i]->goBack(restPos);
            } else if (!shots[i]->revert) {
                shots[i]->activate(target);
            }
        } else { //not active
            sf::Vector2f restPos = shots[i]->calcStartPos(playerPos, playerFacingRight, i);
            shots[i]->restPosition(restPos);
        }
        shots[i]->animateMovement();
    }
}

void PiercingShotManager::render(sf::RenderWindow& window) const {
    for (const auto& shot : shots) {
        shot->render(window);
    }
}

//------------SHOT

PiercingShot::PiercingShot() :
    debuff(0, 0),
    //checks
    active(false), revert(false), hit(false),
    //buffer
    timerAfterHit(0.0f), cooldownAfterHit(1.5f),
    //movement
    move(0.0f, 0.0f), speed(1000.0f)
{
    collisionType = BOX; entityType = COLLISION_ABILITY; stun = false;
    //
    sprite.setTexture(*textures["piercingShot"]);
    bounds = sf::FloatRect(2, 0, 17, 18);
    hitBox.updateSize(bounds);
    sprite.setOrigin(sf::Vector2f((bounds.left + bounds.width/2.0f), (bounds.top + bounds.height/2.0f)));
}

sf::Vector2f PiercingShot::calcStartPos(const sf::Vector2f& playerPosition, bool playerFacingRight, size_t num) {
    sf::Vector2f position;
    float offsetX = 32.0f;
    float offsetY = (num*20.0f) + 7.0f;

    if (playerFacingRight) {
        position.x = playerPosition.x - offsetX;
    } else {
        position.x = playerPosition.x + offsetX;
    }
    position.y = playerPosition.y - offsetY;

    return position;
}

void PiercingShot::restPosition(const sf::Vector2f& restPosition) {
    sprite.setPosition(restPosition.x, restPosition.y);
    hitBox.followEntity(sprite.getPosition());
    sprite.rotate(0.0f);
}

void PiercingShot::applyMovement(const sf::Vector2f& target) {
    move = sf::Vector2f(0.0f, 0.0f); 
    sf::Vector2f direction = normalize(target);
    move = direction*speed;
    sf::Vector2f frameMove = move*DeltaTime::getInstance()->getDeltaTime();
    sprite.move(frameMove);
    hitBox.followEntity(sprite.getPosition());
}

void PiercingShot::activate(const sf::Vector2f& toEnemy) {
    sf::Vector2f toTarget = toEnemy - getPosition();
    if (magnitude(toTarget) <= 5.0f) {
        hit = true;
        return;
    }
    applyMovement(toTarget);
}

void PiercingShot::goBack(const sf::Vector2f& toRest) {
    sf::Vector2f toTarget = toRest - getPosition();
    if (magnitude(toTarget) <= 5.0f) {
        active = false;
        revert = false;
        return;
    }
    applyMovement(toTarget);
}

void PiercingShot::animateMovement() {
    float rotationSpeed = active ? 1080.0f : 180.0f;  
    float frameRotation = rotationSpeed * DeltaTime::getInstance()->getDeltaTime();
    
    sprite.rotate(frameRotation);
}

void PiercingShot::afterHitBuffer() {
    timerAfterHit += DeltaTime::getInstance()->getDeltaTime();
    animateMovement();

    if (timerAfterHit >= cooldownAfterHit) {
        timerAfterHit = 0.0f;
        revert = true;
        hit = false;
    }
}

//returns dmg blast will deal
sf::Vector2u PiercingShot::hitEnemy() {
    if (active) {
        return debuff;
    } else {
        return sf::Vector2u(0, 0);
    }
}

sf::FloatRect PiercingShot::getBounds() const {
    return hitBox.getBounds();
}