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
    bounds = sf::FloatRect(45, 70, 59, 49);
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
    size_t ability = slime.getState();
    if (ability == 1) {
        player.takeDebuffs(5.0f, 0.0f);
    } else if (ability == 2) {
        player.takeDebuffs(10.0f, 50.0f);
    }
}

//ENTITY FUNCTIONS

size_t Slime::getState() {
    return currentAbility; 
}

const sf::Shape& Slime::getShape() {
    return hitBox.body;
}

void Slime::render(sf::RenderWindow& window) {
    window.draw(sprite);
    window.draw(hitBox.body);
}


//SlimePool class
SlimePool::SlimePool():
    totalSlime(100), currentSlime(10)
{
    for(int i = 0; i < totalSlime; i++){
        auto slime = std::make_shared<Slime>();
        pool.push_back(slime); 
    }
}

std::vector<std::shared_ptr<Slime>> SlimePool::getSlimes(sf::Vector2u& resolution) {
    for(int i = 0; i < currentSlime; i++) {
        if(!pool.empty()) {
            auto slime = pool.back(); 
            pool.pop_back(); 
            slime->setInitialPosition(resolution); 
            activeSlimes.push_back(slime); 
            //? if new wave comes before finishing the last wave then this needs to be changed.
        }
        else {
            break;
        }
    }
    return activeSlimes; 
    //can put logic to expand slime code if needed. (for safety)
}