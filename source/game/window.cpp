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

void Screen::handleEvents() {
    while(window->pollEvent(event)) {
        switch(event.type) {
            case sf::Event::Closed:
                window->close(); 
                break;
            case sf::Event::KeyPressed:
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window->close();
                }
                break; 
            default:
                break; 
        }
        kingdom.handleEvents(*window, event); 
    }
}

void Screen::update() { 
    kingdom.update(*window, event); 
}


void Screen::render() {
    window->clear(); 
    kingdom.render(*window); 
    window->display(); 
}