#include "../header/battle/player/abilities/blast.h"

BlastPool::BlastPool(size_t totalBlasts) : totalBlasts(totalBlasts) {
    for (size_t i = 0; i < totalBlasts; ++i) {
        allBlasts.emplace_back(std::make_unique<Blast>());
    }
}

void BlastPool::currentBlasts(const sf::Vector2f& mousePosition, const sf::Vector2f& playerPosition, GridSystem& grid) {
    if (fireCooldown.getElapsedTime().asSeconds() >= 0.15f) {
        auto blast = std::move(allBlasts.back());
        allBlasts.pop_back();
        blast->startPosition(playerPosition);
        blast->activate(mousePosition, playerPosition);
        grid.addEntity(*blast);
        activeBlasts.push_back(std::move(blast));
        fireCooldown.restart();
    }
}

void BlastPool::update(const sf::FloatRect screenBounds) {
    for (const auto& blast : activeBlasts) {
        blast->isActive(screenBounds);
    }
}

void BlastPool::resetBlasts() {
    for (auto it = activeBlasts.begin(); it != activeBlasts.end(); ) {
        if (!(*it)->alive) {
            allBlasts.push_back(std::move(*it));
            it = activeBlasts.erase(it);
        } else {
            (*it)->update((*it)->move);
            ++it;
        }
    }
}

void BlastPool::render(sf::RenderWindow& window) const {
    for (const auto& blast : activeBlasts) {
        blast->render(window);
    }
}



//------------------


Blast::Blast() {
    collisionType = CIRCLE; entityType = BLAST;
    animationSheetDim = sf::Vector2u(4, 1); frameDuration = 0.15f; 
    sprite.setTexture(*textures["blast"]);
    animation = Animation(*textures["blast"], animationSheetDim, frameDuration);
    sprite.setTextureRect(animation.uvRect);
    hitBox = CircleCollision();
    bounds = sf::FloatRect(140, 140, 22, 22);

    hitBox.updateSize(bounds);
    sprite.setOrigin(sf::Vector2f((bounds.left + bounds.width/2.0f), (bounds.top + bounds.height/2.0f)));
    sprite.setScale(0.1f, 0.1f);

    blastSpeed = 600.0f;
    stun = false;
}

sf::Vector2f Blast::hitEnemy() {
    return sf::Vector2f(10.0f, 0.0f);
}

void Blast::kill() {
    alive = false;
};

void Blast::startPosition(const sf::Vector2f& playerPosition) {
    sprite.setPosition(playerPosition.x + sprite.getGlobalBounds().width/2.0f + 8.0f, playerPosition.y - 3.0f);
    hitBox.followEntity(sprite.getPosition());
}

void Blast::activate(const sf::Vector2f& mousePosition, const sf::Vector2f& playerPosition) {    
    sf::Vector2f direction = normalize(mousePosition - playerPosition);

    move = direction*blastSpeed*DeltaTime::getInstance()->getDeltaTime();

}

void Blast::update(sf::Vector2f move) {
    sprite.move(move);
    hitBox.followEntity(sprite.getPosition());
    animation.update(sprite, 0, true, {0.1f, 0.1f});
}

void Blast::isActive(const sf::FloatRect screenBounds) {
    sf::Vector2f direction = sprite.getPosition() - previousPosition;
    previousPosition = sprite.getPosition();
    
    sf::Vector2f position;
    if (direction.x > 0) {
        position.x = sprite.getPosition().x - sprite.getGlobalBounds().width;
    } else {
        position.x = sprite.getPosition().x + sprite.getGlobalBounds().width;
    }

    if (direction.y > 0) {
        position.y = sprite.getPosition().y - sprite.getGlobalBounds().height;
    } else {
        position.y = sprite.getPosition().y + sprite.getGlobalBounds().height;
    }

    alive = screenBounds.contains(position);
}

sf::FloatRect Blast::getBounds() const {
    return hitBox.body.getGlobalBounds();
}

void Blast::render(sf::RenderWindow& window) const {
    window.draw(sprite);
    // window.draw(hitBox.body);
}