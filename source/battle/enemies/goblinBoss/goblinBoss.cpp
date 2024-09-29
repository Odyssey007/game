#include "../header/battle/enemies/goblinBoss/goblinBoss.h"

const float BASE_MOVEMENT_SPEED = 150.0f;
const float BASE_SLOW = 0.0f; //done in %
const float BASE_DMG = 15.0f;
const float BASE_HP = 200.0f;

GoblinBoss::GoblinBoss() {
    collisionType = BOX; 
    //update enemy-parent
    movementSpeed = BASE_MOVEMENT_SPEED;
    debuff = {BASE_DMG, BASE_SLOW}; health = BASE_HP;
    bounds = {35, 35, 75, 90}; usingAbility = false;
    //
    scale = 1.0f;
    sprite.setTexture(*textures["goblinBoss"]);
    animationSheetDim = sf::Vector2u(4, 1); frameDuration = 0.22f;
    animation = Animation(*textures["goblinBoss"], animationSheetDim, frameDuration);
    hitBox.updateSize(bounds);
    sprite.setTextureRect(animation.uvRect);
    sprite.setOrigin(sf::Vector2f((bounds.left + bounds.width/2.0f), (bounds.top + bounds.height/2.0f)));
}

void GoblinBoss::addExtra(GridSystem& grid) {
    grid.addEntity(bodySlam);
}

void GoblinBoss::update(const sf::Vector2f& target) {
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
        facingRight = true;
    } else if (toTarget.x < 0) {
        facingRight = false;
    }
    //animation
    if (isMoving) {
        animation.update(sprite, 0, facingRight, {scale, scale});
    } else {
        animation.resetToFirst(sprite, facingRight, {scale, scale});
    }
    //buffers
    if (bodySlam.cooldown(usingAbility)) {
        return;
    } 
    if (bulletSpray.cooldown(usingAbility)) {
        return;
    } 
    //movement
    if (!hitPlayer && !usingAbility) {
        isMoving = true;
        meleeMovement(target);
    } else if (hitPlayer){
        hitPlayer = false;
        debuff = {BASE_DMG, BASE_SLOW};
    }
    hitBox.followEntity(sprite.getPosition());
}

void GoblinBoss::updateAbility(const sf::Vector2f& target, const sf::FloatRect& screenBounds, GridSystem& grid) {
    float dist = distance(target, sprite.getPosition());
    //ability1: bodySlam
    if ((bodySlam.isAlive() || (dist < 225.0f && bodySlam.canSlam())) && !bulletSpray.isAlive()) {
        isMoving = false;
        usingAbility = true;
        //
        bodySlam.activate(sprite.getPosition());
    }  
    //ability2: bulletSpray
    else if (bulletSpray.isAlive() || (dist < 500.0f && bulletSpray.canCast())) {
        isMoving = false;
        usingAbility = true;
        //
        bulletSpray.activate(sprite.getPosition(), grid);
        bulletSpray.update(screenBounds, sprite.getPosition());
    }
}

void GoblinBoss::abilityCleanUp() {
    bulletSpray.cleanUp();
}

void GoblinBoss::checkLvlUp(const size_t level) {
    if (level == 0) return;
    health += BASE_HP*level*0.1f;
    debuff.x += BASE_DMG*level*0.05f;
    movementSpeed += BASE_MOVEMENT_SPEED*level*0.005f;
}

sf::Vector2f GoblinBoss::attack() {
    return debuff;
}

sf::FloatRect GoblinBoss::getBounds() const {
    return hitBox.getBounds();
}

sf::Vector2f GoblinBoss::getPosition() const {
    return sprite.getPosition();
}

void GoblinBoss::render(sf::RenderWindow& window) const {
    if (bodySlam.canSlam()) {
        bodySlam.render(window);
    }
    if (bulletSpray.canCast()) {
        bulletSpray.render(window);
    }
    window.draw(sprite);
}