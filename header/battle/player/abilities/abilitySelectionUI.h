#pragma once
#include "../header/utility.h"

//TODO implement card contents&&return which ability picked
//TODO implement what abilities show up 
class AbilitySelectionUI {
private:
    bool picked; sf::RectangleShape* selectedAbility = nullptr;
    std::vector<sf::RectangleShape> abilityCards;
    sf::RectangleShape confirmBtn;
    sf::Font font;
    sf::Text confirmText;
public:
    void confirmAbility(sf::Mouse::Button button, const sf::Vector2f& mousePos, GameState& state);
    AbilitySelectionUI();
    void update(uint8_t curLvl, uint8_t& lastLvl, GameState& state);
    void spawnCards(const sf::FloatRect& screenBounds);
    void render(sf::RenderWindow& window) const;
};