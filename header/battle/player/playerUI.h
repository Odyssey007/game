#pragma once 
#include "../header/utility.h"

class PlayerUI {
private:
    //hp
    float maxHpSize;
    sf::Vector2f hpBarSize;
    sf::RectangleShape hpBar;
    sf::RectangleShape hpBarOutline;
    //exp
    float maxExpSize; float expBorderThickness;
    sf::Vector2f expBarSize;
    sf::RectangleShape expBar;
    sf::RectangleShape expBarOutline;
    //lvl
    sf::Font lvlFont;
    sf::Text lvlText;

    void setHpBar(const sf::FloatRect& screenBounds, float playerHealth);
    void setExpBar(const sf::FloatRect& screenBounds, float playerExp);
    void setLvlText(const sf::FloatRect& screenBounds, uint8_t playerLvl);
public:
    PlayerUI() = default;
    PlayerUI(float screenWidth);

    void update(const sf::FloatRect& screenBounds, 
                float playerHp, float playerExp, int playerLvl);
    void render(sf::RenderWindow& window);
};