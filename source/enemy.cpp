#include "../header/enemy.h"

Enemy::Enemy() :
    movementSpeed(220.0f), bestDirection(sf::Vector2f(1, 1)),
    attackBuffer(0.25f), attacking(false), recovering(false), 
    attackDistance(250.0f), totalDistanceAttack(0.0f)
{
    //load slime texture
    if (!this->slime_texture.loadFromFile("assets/slime.png")) {
        throw std::runtime_error ("Failed to load player texture");
    }
    this->slime_sprite.setTexture(slime_texture);
    
    generateDirections();

    //makes the center the middle of the img
    spriteBounds = slime_sprite.getLocalBounds();
    slime_sprite.setOrigin(spriteBounds.width / 2.0f, spriteBounds.height / 2.0f);
}

//generates all the directions of possible movement
void Enemy::generateDirections(int numDirections) {
    const float zeroTreshhold = 1e-6; //to stop floating point precission eeror
    directions.clear();
    for (int i = 0; i < numDirections; i++) {
        float angle = 2 * M_PI * i / numDirections;
        float x = std::cos(angle);
        float y = std::sin(angle);
        if (std::abs(x) < zeroTreshhold) x = 0;
        if (std::abs(y) < zeroTreshhold) y = 0;
        directions.push_back(sf::Vector2f(x, y));
    }
}


void Enemy::movement(const sf::Vector2f& target, float deltaTime) {
    //check if can attack
    if (attacking) {
        doAttack(deltaTime);
        return;
    }
    //check if needs to recover after attack
    if (recovering) {
        if (attackBuffer > 0) {
            attackBuffer -= deltaTime;
            return;
        }
        recovering = false;
    } else {
        attackBuffer = 0.25f; //resets buffer
    }

    //checks if in attack distance 
    if (distance(target, slime_sprite.getPosition()) <= 100.0f) {
        attacking = true;
        return;
    }

    //idle movement ie. moves toward the player
    sf::Vector2f toTarget = target - slime_sprite.getPosition();
    toTarget = normalize(toTarget);

          //finds the optimal direction toward target 
    float maxDot = -1.0f;
    for (int i = 0; i < 16; i++) {
        float dot = dotProduct(directions[i], toTarget);
        if (dot > maxDot) {
            maxDot = dot;
            bestDirection = directions[i];
        }
    }

    sf::Vector2f move = bestDirection*movementSpeed*deltaTime;
    slime_sprite.move(move);
}


void Enemy::doAttack(float deltaTime) {
    //buffers attack
    if (attackBuffer > 0) {
        attackBuffer -= deltaTime;
        return;
    }
    //attacks
    if (totalDistanceAttack < attackDistance) {
        float moveForFrame  = 3.5*movementSpeed*deltaTime;
        sf::Vector2f move = bestDirection*moveForFrame;
        slime_sprite.move(move);
        totalDistanceAttack += sqrt(move.x*move.x + move.y*move.y);
    } else if (totalDistanceAttack >= attackDistance) { //reset values after attack
        attacking = false;
        totalDistanceAttack = 0.0f;
        recovering = true;
        attackBuffer = 0.25f;
    }
}