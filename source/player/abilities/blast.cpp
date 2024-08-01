#include "../header/player/abilities/blast.h"

BlastPool::BlastPool(size_t totalBlasts) : totalBlasts(totalBlasts) {
    for (size_t i = 0; i < totalBlasts; ++i) {
        allBlasts.emplace_back(std::make_shared<Blast>());
    }
}

void BlastPool::currentBlasts(const sf::Vector2f& mousePosition, const sf::Vector2f& playerPosition) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !allBlasts.empty()) {
        std::shared_ptr<Blast> blast = allBlasts.back();
        allBlasts.pop_back();
        blast->startPosition(playerPosition);
        blast->activate(mousePosition, playerPosition);
        activeBlasts.push_back(blast);
    }
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
    body.setFillColor(sf::Color::Red);
    body.setRadius(10.0f);
    body.setOrigin(sf::Vector2f(5, 5));

    blastSpeed = 700;
    active = false;
}

void Blast::startPosition(const sf::Vector2f& playerPosition) {
    body.setPosition(playerPosition + sf::Vector2f(body.getRadius() + 1, body.getRadius() + 1));
}

void Blast::activate(const sf::Vector2f& mousePosition, const sf::Vector2f& playerPosition) {
    active = true;
    
    sf::Vector2f direction = normalize(mousePosition - playerPosition);

    move = direction*blastSpeed*DeltaTime::getInstance()->getDeltaTime();
}

void Blast::update(sf::Vector2f move) {
    body.move(move);
}

bool Blast::isActive(const sf::FloatRect screenBounds) const {
    sf::Vector2f position;
    position.x = body.getPosition().x + body.getRadius();
    position.y = body.getPosition().y + body.getRadius();
    
    return screenBounds.contains(position);
}

void Blast::render(sf::RenderWindow& window) const {
    window.draw(body);
}
