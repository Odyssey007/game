#pragma once
#include "../header/utility.h"

//TODO implement return which ability picked && wrapping when too big

class AbilitySelectionUI {
private:
    bool picked; sf::RectangleShape* selectedAbility = nullptr;
    std::vector<sf::RectangleShape> abilityCards;
    sf::RectangleShape confirmBtn;
    sf::Font font;
    sf::Text confirmText;
    //
    std::vector<uint8_t> availableAbilities;
    std::vector<uint8_t> givenAbilities;
    std::vector<std::pair<sf::Text, sf::Text>> abilityDescription;
    int generateAbility();
    void writeDescription(uint8_t ability);
    void wrapText(sf::Text& text, float maxWidth);
public:
    void confirmAbility(sf::Mouse::Button button, const sf::Vector2f& mousePos, GameState& state);
    AbilitySelectionUI();
    void update(uint8_t curLvl, uint8_t& lastLvl, GameState& state);
    void spawnCards(const sf::FloatRect& screenBounds);
    void render(sf::RenderWindow& window) const;
};

/* ABILITY LOC
    0-atomicBullet
    1-energyBarrier
    2-piercingShot
    3-maxHealth     --
    4-health regeneration
    5-move speed
    6-heal
    7-dmg increase
    8-ability cooldown
*/