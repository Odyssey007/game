#include "../header/battle/player/playerUI.h"

PlayerUI::PlayerUI(float screenWidth) {
    //hp
    maxHpSize = 325.0f; hpBarSize = sf::Vector2f(maxHpSize, 20.0f);
    hpBarOutline.setOutlineThickness(1.5f);
    hpBarOutline.setOutlineColor(sf::Color(255, 255, 255, 128));
    hpBarOutline.setFillColor(sf::Color(255, 255, 255, 0));
    hpBarOutline.setSize(hpBarSize);
    hpBar.setFillColor(sf::Color(255, 0, 0, 200));
    hpBar.setOutlineThickness(0.0f);
    hpBar.setSize(hpBarSize);
    //exp
    maxExpSize = screenWidth-6; expBorderThickness = 3.0f; 
    expBarSize = sf::Vector2f(maxExpSize, 25.0f);
    expBarOutline.setOutlineThickness(expBorderThickness);
    expBarOutline.setOutlineColor(sf::Color(255, 255, 255, 128));
    expBarOutline.setFillColor(sf::Color(255, 255, 255, 0));
    expBarOutline.setSize(expBarSize);
    expBar.setFillColor(sf::Color(50, 70, 200));
    expBar.setOutlineThickness(0.0f);
    expBar.setSize(expBarSize);
    //lvl
    lvlFont.loadFromFile("assets/fonts/munro.ttf");
    lvlText.setFont(lvlFont);
    lvlText.setCharacterSize(20);
    lvlText.setFillColor(sf::Color::White);
}

void PlayerUI::update(const sf::FloatRect& screenBounds, 
                      float playerHp, float playerExp, int playerLvl) {
    setHpBar(screenBounds, playerHp);
    setExpBar(screenBounds, playerExp);
    setLvlText(screenBounds, playerLvl);
}

void PlayerUI::setLvlText(const sf::FloatRect& screenBounds, uint8_t playerLvl) {
    //position
    sf::Vector2f position(
        screenBounds.left + screenBounds.width - lvlText.getGlobalBounds().width - 15.0f,
        screenBounds.top + 0.8f
    );
    lvlText.setPosition(position.x, position.y);
    //new lvl
    lvlText.setString("Lvl " + std::to_string(playerLvl));
}

void PlayerUI::setExpBar(const sf::FloatRect& screenBounds, float playerExp) {
    //position
    sf::Vector2f position(screenBounds.left+expBorderThickness, screenBounds.top+expBorderThickness);
    expBarOutline.setPosition(position);
    expBar.setPosition(position);
    //size
    expBarSize.x = maxExpSize*playerExp;
    // expBarOutline.setSize(expBarSize);
    expBar.setSize(expBarSize);
}

void PlayerUI::setHpBar(const sf::FloatRect& screenBounds, float playerHealth) {
    //position
    sf::Vector2f position(
        screenBounds.left + 10.0f , 
        screenBounds.top + screenBounds.height - hpBarSize.y - 20.0f
    );
    hpBarOutline.setPosition(position);
    hpBar.setPosition(position);
    //size
    hpBarSize.x = maxHpSize*playerHealth;
    // hpBarOutline.setSize(hpBarSize);
    hpBar.setSize(hpBarSize);
}

void PlayerUI::render(sf::RenderWindow& window) {
    //exp bar
    window.draw(expBarOutline);
    window.draw(expBar);
    window.draw(lvlText);
    //health bar
    window.draw(hpBarOutline);
    window.draw(hpBar);
}