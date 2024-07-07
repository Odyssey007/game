#include "../header/slime.h"

Slime::Slime() :
    //ability
    currentAbility(0), firstAttack(true),
    //leap buffers
    leaping(false), chargeTimer(0.35f), needToRecover(false), recoveryTimer(0.35f),
    //leap distance
    leapDistance(150.0f), totalLeapDistance(0.0f)
{
    //preliminaries
    enemyType = SLIME; collisionType = CIRCLE;
    sprite.setTexture(textures["slime"]);
    //hit box
    hitBox = CircleCollision();
    bounds = sf::IntRect(45, 70, 59, 49);
    hitBox.updateSize(bounds);
    //set origin and position
    sprite.setOrigin(sf::Vector2f((bounds.left + bounds.width/2.0f), (bounds.top + bounds.height/2.0f)));
}

void Slime::update(const sf::Vector2f& target, const float canLeap) {
    // Check if recovery buffer is needed for attack  
    if (needToRecover) {
        if (recoveryTimer > 0) {
            recoveryTimer -= DeltaTime::getInstance()->getDeltaTime();
            return;
        }
        needToRecover = false;
    }
    //moves
    hitBox.followEntity(sprite.getPosition());
    if (distance(target, sprite.getPosition()) >= canLeap && !leaping) {
        meleeMovement(target);
    } else { //attacks
        attacks();
    }
}

void Slime::attacks() {
    if (firstAttack) {
        leapAttack();
    }
    normalAttack();
}

void Slime::normalAttack() {
    currentAbility = 1;
}

void Slime::leapAttack() {
    currentAbility = 2;
    if (!leaping) {
        chargeTimer -= DeltaTime::getInstance()->getDeltaTime();
        if (chargeTimer <= 0) {
            leaping = true;
        }
    }
    if (totalLeapDistance < leapDistance && leaping) {
        float moveFrame = 5.5 * movementSpeed * DeltaTime::getInstance()->getDeltaTime();
        sf::Vector2f move = bestDirection * moveFrame;
        sprite.move(move);
        totalLeapDistance += magnitude(move);
    } else if (leaping) {
        totalLeapDistance = 0.0f;
        //start buffer
        leaping = false;
        chargeTimer = 0.35f;
        //end buffer
        needToRecover = true;
        recoveryTimer = 0.35f;
        //
        firstAttack = false;
    }
}

size_t Slime::getState() {
    return currentAbility; 
}

//returns hit box body
sf::Shape& Slime::getShape() {
    return hitBox.body;
}

//renders player && player-related render
void Slime::render(sf::RenderWindow& window) {
    window.draw(sprite);
    window.draw(hitBox.body);
}

void Slime::playerContact(Player& player, Entity& slime) {
    size_t ability = slime.getState();
    if (ability == 1) {
        player.takeDebuffs(5.0f, 0.0f);
    } else if (ability == 2) {
        player.takeDebuffs(10.0f, 50.0f);
    }
}