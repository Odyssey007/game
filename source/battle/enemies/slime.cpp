#include "../header/battle/enemies/slime.h"

Slime::Slime() :
    //ability
    firstAttack(true),
    //leap buffers
    leaping(false), chargeTimer(0.35f), needToRecover(false), recoveryTimer(0.35f),
    //leap distance
    leapDistance(150.0f), totalLeapDistance(0.0f)
{
    //preliminaries
    enemyType = SLIME; collisionType = CIRCLE;
    sprite.setTexture(*textures["slime"]);
    //hit box
    hitBox = CircleCollision();
    bounds = sf::FloatRect(45, 70, 59, 49);
    hitBox.updateSize(bounds);
    //hitBoxBody = std::make_shared<sf::CircleShape>(hitBox.body);
    //set origin and position
    sprite.setOrigin(sf::Vector2f((bounds.left + bounds.width/2.0f), (bounds.top + bounds.height/2.0f)));
}

void Slime::update(const sf::Vector2f& target) {
    // Check if recovery buffer is needed for attack  
    if (needToRecover) {
        if (recoveryTimer > 0) {
            recoveryTimer -= DeltaTime::getInstance()->getDeltaTime();
            return;
        }
        needToRecover = false;
    }

    float canLeap = 100.0f;

    //moves
    if (distance(target, sprite.getPosition()) >= canLeap && !leaping) {
        meleeMovement(target);
    } else { //attacks
        attacks();
    }
    //!problem with hitbox when leap attack it doesn't track for a sec
    hitBox.followEntity(sprite.getPosition());
}

void Slime::attacks() {
    // if (firstAttack) {
    //     leapAttack();
    // }
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

//static function
void Slime::playerContact(Player& player, Entity& slime) {
    player.takeDebuffs(5.0f, 0.0f);
    // size_t ability = slime.getState();
    // if (ability == 1) {
    //     player.takeDebuffs(5.0f, 0.0f);
    // } else if (ability == 2) {
    //     player.takeDebuffs(10.0f, 50.0f);
    // }
}

//ENTITY FUNCTIONS

sf::FloatRect Slime::getBounds() const {
    return hitBox.body.getGlobalBounds();
}

sf::Vector2f Slime::getPosition() const {
    return hitBox.body.getPosition();
}

void Slime::render(sf::RenderWindow& window) const {
    window.draw(sprite);
    window.draw(hitBox.body);
}