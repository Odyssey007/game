#include "../header/battle/enemies/goblinMiniBoss.h"

const float BASE_MOVEMENT_SPEED = 200.0f;
const float BASE_SLOW = 0.0f; //done in %
const float BASE_DMG = 15.0f;
const float BASE_HP = 200.0f;
//ABILITY 1
const float ABILITY1_SLOW = 0.25f;
const float ABILITY1_DMG = 20.0f;

GoblinMiniBoss::GoblinMiniBoss() : 
    scale(1.3f), //mini
    shouldBlink(true), cooldown(5.0f), cooldownAfter(1.0f) //ability1
{
    collisionType = BOX; //update entity-parent
    //update enemy-parent
    movementSpeed = BASE_MOVEMENT_SPEED;
    debuff = {BASE_DMG, BASE_SLOW}; health = BASE_HP;
    bounds = sf::FloatRect(0, 0, 38, 47);
    //mini-boss
    sprite.setColor(sf::Color(236, 59, 59));
    sprite.setScale(scale, scale);
    //
    sprite.setTexture(*textures["goblin"]);
    animationSheetDim = sf::Vector2u(4, 1);
    animation = Animation(*textures["goblin"], animationSheetDim, frameDuration);
    hitBox.updateSize(bounds);
    sprite.setTextureRect(animation.uvRect);
    sprite.setOrigin(sf::Vector2f((bounds.left + bounds.width/2.0f), (bounds.top + bounds.height/2.0f)));
}

void GoblinMiniBoss::update(const sf::Vector2f& target) {
    //slow effects
    if (isSlowed) {
        slowDuration -= DeltaTime::getInstance()->getDeltaTime();
    }
    if (isSlowed && slowDuration <= 0) {
        isSlowed = false;
        slowDuration = 1.0f;
        movementSpeed = BASE_MOVEMENT_SPEED;
    }
    //facing direction
    sf::Vector2f toTarget = target - sprite.getPosition();
    toTarget = normalize(toTarget);
    if (toTarget.x >= 0) {
        facingRight = false;
    } else if (toTarget.x < 0) {
        facingRight = true;
    }
    //animation
    if (isMoving) {
        animation.update(sprite, 0, facingRight, {scale, scale});
    } else {
        animation.resetToFirst(sprite, facingRight, {scale, scale});
    }
    //cooldown for blink
    if (!shouldBlink && cooldown >= 0.0f) {
        cooldown -= DeltaTime::getInstance()->getDeltaTime();
        if (cooldown <= 0.0f) {
            shouldBlink = true;
        }
    }
    //cooldown after blink
    if (cooldownAfter > 0.0f) {
        cooldownAfter -= DeltaTime::getInstance()->getDeltaTime();
        isMoving = false;
        return;
    }
    //movement
    if (!hitPlayer) {
        meleeMovement(target);
        isMoving = true;
    } else {
        hitPlayer = false;
        debuff.x = BASE_DMG;
        debuff.y = BASE_SLOW;
    }
    hitBox.followEntity(sprite.getPosition());
    //ability1: blink activate
    if (distance(target, sprite.getPosition()) < 300.0f && shouldBlink) {
        blinkBehind(target);
        cooldown = 5.0f;
        shouldBlink = false;
        cooldownAfter = 0.5f;
        isMoving = false;
    }
}

void GoblinMiniBoss::blinkBehind(const sf::Vector2f& target) {
    debuff.x = ABILITY1_DMG;
    debuff.y = ABILITY1_SLOW;
    //
    sf::Vector2f toTarget = target - sprite.getPosition();
    toTarget = normalize(toTarget);

    float offsetDistance;
    if (std::abs(moveDistance.x) > std::abs(moveDistance.y)) { //moving hor
        offsetDistance = -55.0f;
    } else { //moving vert
        if (moveDistance.y >= 0) { //going down
            offsetDistance = -85.0f;
        } else { //going up
            offsetDistance = -75.0f;
        }
    }
    sf::Vector2f newPosition = target + toTarget*offsetDistance;

    sprite.setPosition(newPosition);
    hitBox.followEntity(newPosition);
}

void GoblinMiniBoss::checkLvlUp(const size_t level) {
    if (level == 0) return;
    health += BASE_HP*level*0.1f;
    debuff.x += BASE_DMG*level*0.05f;
    movementSpeed += BASE_MOVEMENT_SPEED*level*0.005f;
}

sf::Vector2f GoblinMiniBoss::attack() {
    return debuff;
}

sf::FloatRect GoblinMiniBoss::getBounds() const {
    return hitBox.getBounds();
}

sf::Vector2f GoblinMiniBoss::getPosition() const {
    return sprite.getPosition();
}