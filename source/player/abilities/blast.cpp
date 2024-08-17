#include "../header/player/abilities/blast.h"

BlastPool::BlastPool(size_t totalBlasts) : totalBlasts(totalBlasts) {
    for (size_t i = 0; i < totalBlasts; ++i) {
        allBlasts.emplace_back(std::make_shared<Blast>());
    }
}

void BlastPool::currentBlasts(const sf::Vector2f& mousePosition, const sf::Vector2f& playerPosition) {
    bool isMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if (isMousePressed && !wasMousePressed && !allBlasts.empty()) {
        std::shared_ptr<Blast> blast = allBlasts.back();
        allBlasts.pop_back();
        blast->startPosition(playerPosition);
        blast->activate(mousePosition, playerPosition);
        activeBlasts.push_back(blast);
    }

    wasMousePressed = isMousePressed;
}

void BlastPool::resetBlasts(const sf::FloatRect screenBounds) {
    auto it = activeBlasts.begin();
    while (it != activeBlasts.end()) {
        if (!(*it)->isActive(screenBounds)) {
            allBlasts.push_back(*it);
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
    animationSheetDim = sf::Vector2u(4, 1); frameDuration = 0.15f; 
    sprite.setTexture(*textures["blast"]);
    animation = Animation(*textures["blast"], animationSheetDim, frameDuration);
    sprite.setTextureRect(animation.uvRect);
    hitBox = CircleCollision();
    bounds = sf::FloatRect(140, 140, 22, 22);

    hitBox.updateSize(bounds);
    sprite.setOrigin(sf::Vector2f((bounds.left + bounds.width/2.0f), (bounds.top + bounds.height/2.0f)));
    sprite.setScale(0.1f, 0.1f);

    blastSpeed = 150.0f;
}

void Blast::startPosition(const sf::Vector2f& playerPosition) {
    sprite.setPosition(playerPosition.x + sprite.getGlobalBounds().width/2.0f + 8.0f, playerPosition.y - 3.0f);
    hitBox.followEntity(sprite.getPosition());
}

void Blast::activate(const sf::Vector2f& mousePosition, const sf::Vector2f& playerPosition) {
    alive = true;
    
    sf::Vector2f direction = normalize(mousePosition - playerPosition);

    move = direction*blastSpeed*DeltaTime::getInstance()->getDeltaTime();

}

void Blast::update(sf::Vector2f move) {
    sprite.move(move);
    animation.update(sprite, 0, true, {0.1f, 0.1f});
}

bool Blast::isActive(const sf::FloatRect screenBounds) const {
    sf::Vector2f position;
    position.x = sprite.getPosition().x - sprite.getGlobalBounds().width;
    position.y = sprite.getPosition().y - sprite.getGlobalBounds().width;
    
    return screenBounds.contains(position);
}

void Blast::render(sf::RenderWindow& window) const {
    window.draw(sprite);
    // window.draw(hitBox.body);
}