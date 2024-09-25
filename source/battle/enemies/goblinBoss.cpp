#include "../header/battle/enemies/goblinBoss.h"

const float BASE_MOVEMENT_SPEED = 150.0f;
const float BASE_SLOW = 0.0f; //done in %
const float BASE_DMG = 15.0f;
const float BASE_HP = 200.0f;
//ABILITY 1

//ABILITY 2

GoblinBoss::GoblinBoss() {
    collisionType = BOX; 
    //update enemy-parent
    movementSpeed = BASE_MOVEMENT_SPEED;
    debuff = {BASE_DMG, BASE_SLOW}; health = BASE_HP;
    bounds = {35, 35, 75, 90};
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
    //movement
    if (!hitPlayer && !usingAbility) {
        meleeMovement(target);
        isMoving = true;
    } else if (hitPlayer){
        hitPlayer = false;
        debuff = {BASE_DMG, BASE_SLOW};
    }
    hitBox.followEntity(sprite.getPosition());
    //ability1: body slam
    if (bodySlam.isAlive() || (distance(target, sprite.getPosition()) < 125.0f && bodySlam.canSlam())) {
        bodySlam.activate(sprite.getPosition());
        isMoving = false;
        usingAbility = true;
    }
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

    window.draw(sprite);
    // window.draw(hitBox.body);
}

//------------

const float INITIAL_SIZE = 7.0F;
const float BASE_SLAM_DMG = 0.0f;
const float BASE_SLAM_SLOW = 0.9f;
const float SLAM_DMG = 25.0f;
const float SLAM_SLOW = 0.0f;

Slam::Slam() :
    //starting-ending buffer
    shouldSlam(true), slamCooldown(3.0f), 
    //enlarging
    slamEnlargeTime(0.0f), slamEnlargeDuration(1.55f), 
    curSize(INITIAL_SIZE), maxSize(60.0f),
    //final slam
    finishedCasting(false), dmgDuration(0.5f)
{
    entityType = ENEMY_ABILITY; alive = false; //update entity-parent
    debuff = {BASE_SLAM_DMG, BASE_SLAM_SLOW};
    //growing slam
    sprite.setRadius(curSize);
    sprite.setFillColor(sf::Color::Yellow);
    sprite.setOrigin(sprite.getRadius(), sprite.getRadius());
    hitBox.updateSize(sprite.getGlobalBounds());
    //max slam
    maxSizeOutline.setRadius(INITIAL_SIZE*maxSize);
    maxSizeOutline.setFillColor(sf::Color::Transparent);
    maxSizeOutline.setOutlineColor(sf::Color::Blue);
    maxSizeOutline.setOutlineThickness(1.0f);
    maxSizeOutline.setOrigin(maxSizeOutline.getRadius(), maxSizeOutline.getRadius());
}

bool Slam::cooldown(bool& abilityActive) {
    if (finishedCasting && dmgDuration >= 0.0f) {
        dmgDuration -= DeltaTime::getInstance()->getDeltaTime();
        if (dmgDuration  <= 0.0f) {
            finishedCasting = false;
            dmgDuration = 0.5f;
            debuff = {BASE_SLAM_DMG, BASE_SLAM_SLOW};
            //
            alive = false;
            shouldSlam = false;
            slamCooldown = 5.0f;
            //
            abilityActive = false;
            return false;
        }
        return true;
    }

    if (!shouldSlam && slamCooldown >= 0.0f) {
        slamCooldown -= DeltaTime::getInstance()->getDeltaTime();
        if (slamCooldown <= 0.0f) {
            shouldSlam = true;
            slamEnlargeTime = 0.0f;
            //
            sprite.setScale(1.0f, 1.0f);
            hitBox.updateSize(sprite.getGlobalBounds());
        }
    }
    return false;
}

bool Slam::canSlam() const {
    return shouldSlam;
}

void Slam::activate(const sf::Vector2f& bossPos) {
    alive = true;
    if (slamEnlargeTime <= slamEnlargeDuration) {
        slamEnlargeTime += DeltaTime::getInstance()->getDeltaTime();
        curSize = INITIAL_SIZE + (maxSize - INITIAL_SIZE) * (slamEnlargeTime / slamEnlargeDuration);
        sprite.setScale(curSize, curSize);
    } else {
        sprite.setScale(maxSize, maxSize);
        curSize = maxSize;
        //
        overrideTimer = true;
        finishedCasting = true;
        debuff = {SLAM_DMG, SLAM_SLOW};
    }
    hitBox.updateSize(sprite.getGlobalBounds());
    //
    sprite.setPosition(bossPos);
    maxSizeOutline.setPosition(bossPos);
    hitBox.followEntity(sprite.getPosition());
}

sf::FloatRect Slam::getBounds() const {
    return hitBox.getBounds();
}

sf::Vector2f Slam::getPosition() const {
    return sprite.getPosition();
}

sf::FloatRect Slam::calcBounds(float scale) {
    sf::FloatRect originalBounds = sprite.getLocalBounds();
    float hitboxScaleFactor = 0.85;
    //scale down
    float adjustedWidth = originalBounds.width * scale * hitboxScaleFactor;
    float adjustedHeight = originalBounds.height * scale * hitboxScaleFactor;
    //center on sprite position
    sf::Vector2f spriteCenter = sprite.getPosition();
    float left = spriteCenter.x - adjustedWidth / 2;
    float top = spriteCenter.y - adjustedHeight / 2;
    //
    return sf::FloatRect(left, top, adjustedWidth, adjustedHeight);
}

void Slam::render(sf::RenderWindow& window) const {
    if (alive) {
        window.draw(sprite);
        window.draw(maxSizeOutline);
    }
}