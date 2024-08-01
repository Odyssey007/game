#include "../header/player/abilities/dash.h"

Dash::Dash() {
    totalDashDistance = 0;
    dashDistance = 150;
}

void Dash::reset() {
    totalDashDistance = 0;
    dashDistance = 150;
}

// void Dash::activate(sf::Sprite& player, const sf::Vector2f velocity 
//                     const sf::Vector2f& mousePosition, const sf::Vector2f& playerPosition) {
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
//         sf::Vector2f direction = normalize(mousePosition - playerPosition);

//         if (totalDashDistance < dashDistance) {
//             float move = 6*300*DeltaTime::getInstance()->getDeltaTime();
//             sf::Vector2f moveV = direction * move;
//             player.move(moveV);
//             totalDashDistance += magnitude(moveV);
//         }
//     }
// }

void Dash::activate(const sf::Vector2f& mousePosition, const sf::Vector2f& playerPosition) {
    return;
}

void Dash::render(sf::RenderWindow& window) const {
    return;
}