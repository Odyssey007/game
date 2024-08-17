#include "../header/battle/enemies/goblin.h"

Goblin::Goblin() {
    enemyType = SLIME;

    hitBox = BoxCollision();
    hitBox.updateSize(bounds);
    sprite.setOrigin(sf::Vector2f((bounds.left + bounds.width/2.0f), (bounds.top + bounds.height/2.0f)));
}

void Goblin::update(const sf::Vector2f& target) {
    
}

void Goblin::playerContact(Player& player, Entity& slime) {

}

//ENTITY FUNCTIONS

sf::FloatRect Goblin::getBounds() const {
    return hitBox.body.getGlobalBounds();
}

sf::Vector2f Goblin::getPosition() const {
    return hitBox.body.getPosition();
}

void Goblin::render(sf::RenderWindow& window) const {
    window.draw(sprite);
}