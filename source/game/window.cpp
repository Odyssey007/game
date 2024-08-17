#include "../header/game/window.h"

Screen::Screen() {
    sf::VideoMode screen = sf::VideoMode::getDesktopMode();
    window = std::make_unique<sf::RenderWindow>(screen, "Project-AA", sf::Style::Fullscreen);
    window->setFramerateLimit(120);
    kingdom.enter(*window); 
}

bool Screen::winRunning() {
    return window->isOpen(); 
}

void Screen::update() { 
    handleEvents(); 
    kingdom.update(*window, event); 
}

void Screen::handleEvents() {
    while(window->pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            window->close(); 
        } else if(event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) window->close();
        }
    }
}

void Screen::render() {
    window->clear(); 
    kingdom.render(*window); 
    window->display(); 
}