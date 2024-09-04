#include "../header/battle/menu.h"

Menu::Menu() {
    sf::Vector2 size = sf::Vector2f(1500, 700);
    background.setSize(size);
    background.setOrigin(size.x/2, size.y/2);
    background.setPosition(920, 540);
    background.setFillColor(sf::Color(64, 64, 64));
    
    if(!font.loadFromFile("assets/fonts/munro.ttf")) {
        std::cout << "font not working\n";
    }
    
    //resume
    text[0].setString("Resume");
    text[0].setFont(font);
    text[0].setFillColor(sf::Color::White);
    text[0].setCharacterSize(55);
    text[0].setPosition(250, 150);
    //exit
    text[1].setString("Exit");
    text[1].setFont(font);
    text[1].setFillColor(sf::Color::White);
    text[1].setCharacterSize(55);
    text[1].setPosition(1200, 150);
}

void Menu::setPosition(sf::View& view) {
    sf::FloatRect viewBounds(view.getCenter() - view.getSize() / 2.0f, view.getSize());

    sf::Vector2f pos(viewBounds.left+viewBounds.width/2.0f, viewBounds.top+viewBounds.height/2.0f);

    background.setPosition(pos);

    sf::FloatRect resumePos = background.getGlobalBounds();

    sf::Vector2f pose;
    pose.x = resumePos.left + resumePos.width/8.0f;
    pose.y = resumePos.top + resumePos.height/4.0f;

    text[0].setPosition(pose);


    pose.y = pose.y+250;

    text[1].setPosition(pose);
}

void Menu::handleEvent(const sf::Event& event, GameState& state, const sf::Vector2f mousePos) {
    for (size_t i = 0; i < maxOptions; i++) {
        sf::FloatRect textBounds = text[i].getGlobalBounds();
        if (textBounds.contains(static_cast<sf::Vector2f>(mousePos))) {
            text[i].setFillColor(sf::Color::Red);
        } else {
            text[i].setFillColor(sf::Color::White);
        }
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::FloatRect resumeBounds = text[0].getGlobalBounds();
            if (resumeBounds.contains(static_cast<sf::Vector2f>(mousePos))) {
                state = GAME; 
            }
            // sf::FloatRect exitBounds = text[1].getGlobalBounds();
            // if (exitBounds.contains(mousePos)) {
            //     state = EXIT;
            // } 
        }
    }
}

void Menu::render(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(text[0]);
    window.draw(text[1]);
}