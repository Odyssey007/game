#include "../header/battle/enemies/goblinBoss/bodySlam.h"

const float INITIAL_SIZE = 7.0F;
const float BASE_SLAM_DMG = 0.0f;
const float BASE_SLAM_SLOW = 0.75f;
const float SLAM_DMG = 25.0f;
const float SLAM_SLOW = 0.0f;

BodySlam::BodySlam() :
    //starting-ending buffer
    shouldSlam(true), slamCooldown(3.0f), 
    //enlarging
    slamEnlargeTime(0.0f), slamEnlargeDuration(1.55f), 
    curSize(INITIAL_SIZE), maxSize(60.0f),
    //final slam
    finishedCasting(false), dmgDuration(0.2f)
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

bool BodySlam::cooldown(bool& abilityActive) {
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
            return false; //not on cooldown--move
        }
        return true; //on cooldown--stop moving
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
    return false; //on or not on cooldown--can move
}

void BodySlam::activate(const sf::Vector2f& bossPos) {
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

bool BodySlam::canSlam() const {
    return shouldSlam;
}

sf::FloatRect BodySlam::getBounds() const {
    return hitBox.getBounds();
}

sf::Vector2f BodySlam::getPosition() const {
    return sprite.getPosition();
}

sf::FloatRect BodySlam::calcBounds(float scale) {
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

void BodySlam::render(sf::RenderWindow& window) const {
    if (alive) {
        window.draw(sprite);
        window.draw(maxSizeOutline);
    }
}