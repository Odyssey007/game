#pragma once
#include "../header/utility.h"

// struct AbilityInfo {
//     icon
//     description
//     stats?
// }

class AbilitySelectionUI {
private:
    std::vector<sf::RectangleShape> abilityCards;
    sf::RectangleShape confirmBtn;
    void confirmAbility();
public:
    AbilitySelectionUI();
    void update(uint8_t curLvl, uint8_t& lastLvl, GameState& state);
    void spawnCards(const sf::FloatRect& screenBounds);
    void render(sf::RenderWindow& window) const;
};