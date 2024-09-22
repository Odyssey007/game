#include "../header/battle/player/abilities/energyBarrier.h"

EnergyBarrier::EnergyBarrier(GridSystem& grid) : 
    //stats
    active(false), state(0), debuff(5, 0),
    //enlarge
    curScale(2.3f), targetScale(15.0f), elapsedTime(0.0f), scaleDuration(0.5f),
    //pulse
    pulseElapsed(0.0f), frequency(10.1f), minScale(2.3f), maxScale(3.0f)
{
    //preliminaries
    grid.addEntity(*this);
    collisionType = CIRCLE; entityType = TIMED_ABILITY; stun = false;
    animationSheetDim = sf::Vector2u(4, 4); frameDuration = 0.15f;
    //
    animation = Animation(*textures["energyBarrier"], animationSheetDim, frameDuration);
    sprite.setTexture(*textures["energyBarrier"]);
    sprite.setTextureRect(animation.uvRect);
    //
    bounds = sf::FloatRect(-12.0f, -12.0f, 55.0f, 55.0f);
    hitBox.updateSize(bounds);
    //
    sprite.setScale(curScale, curScale);
    sprite.setOrigin(sf::Vector2f((bounds.left + bounds.width/2.0f), (bounds.top + bounds.height/2.0f)));
}

void EnergyBarrier::activate(const sf::Vector2f& playerPos, bool facingRight, bool moving) {
    sf::Vector2f position = {playerPos.x + (facingRight ? -5.0f : 3.0f), playerPos.y - 10.0f};
    if (moving) {
        position.y += 3.0f;
        position.x += facingRight ? 5 : -5;
    }

    sprite.setPosition(position);
    hitBox.followEntity(position);
    animation.update(sprite, state, true, {curScale, curScale});
}

void EnergyBarrier::update(uint8_t& numHits) {
    switch (state) {
        case 0:
            reset();
            break;
        case 2:
            if (numHits == 0) {
                debuff.x = 5;
            } else {
                debuff.x = 5*numHits;
            }
            pulse();
            if (timer.getElapsedTime().asSeconds() >= 3.0f) {
                state++;
                timer.restart();
            }
            break;
        case 3:
            active = true; numHits = 0;
            enlarge();
            break;
    }

    if (timer.getElapsedTime().asSeconds() >= 5.0f) {
        if (numHits == 0) {
            state = 0;
        } else {
            state = (state == 0 ? 2 : state + 1);
        }
        timer.restart();
    }
}

void EnergyBarrier::reset() {
    curScale = 2.3f;
    active = false;
    sprite.setScale(curScale, curScale);
    hitBox.updateSize(bounds);
    //
    debuff.x = 5;
    elapsedTime = 0.0f;
    curScale = 2.3;
    pulseElapsed = 0.0f;
}

void EnergyBarrier::pulse() {
    pulseElapsed += DeltaTime::getInstance()->getDeltaTime();
    float scaleFactor = (sin(pulseElapsed * frequency) + 1) / 2; // Normalize to 0-1
    curScale = minScale + (maxScale - minScale) * scaleFactor;
    sprite.setScale(curScale, curScale);
    hitBox.updateSize(calcBounds(curScale));
    if (elapsedTime >= 2 * M_PI / frequency) elapsedTime = 0;
}

void EnergyBarrier::enlarge() {
    if (elapsedTime <= scaleDuration) {
        elapsedTime += DeltaTime::getInstance()->getDeltaTime();
        curScale = 2.3f + (targetScale - 2.3f) * (elapsedTime / scaleDuration);
        sprite.setScale(curScale, curScale);
    } else {
        sprite.setScale(targetScale, targetScale);
        curScale = targetScale;
        state = 0;
    }
    hitBox.updateSize(calcBounds(curScale));
}

sf::FloatRect EnergyBarrier::calcBounds(float scale) {
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

sf::Vector2u EnergyBarrier::hitEnemy() {
    if (active) {
        return debuff;
    } else {
        return sf::Vector2u(0, 0);
    }
}

sf::FloatRect EnergyBarrier::getBounds() const {
    return hitBox.getBounds();
}