#pragma once
#include "../header/battle/utility.h"


enum GameState { GAME, MENU, EXIT };



class Menu {
private:
    sf::RectangleShape background;
    sf::Font font;
    size_t maxOptions = 2;
    sf::Text text[2];
public:
    Menu();
    void handleEvent(const sf::Event& event, GameState& state, const sf::Vector2f mousePos);
    void setPosition(sf::View& view);
    void render(sf::RenderWindow& window);
};