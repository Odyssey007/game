#include "../header/game.h"

int main() {
    Game game;
    sf::Clock clock; 
    while(game.winRunning()) {
        //update frame
        float deltaTime = clock.restart().asSeconds(); 
        game.update(deltaTime);
        //render the new update
        game.render();
    }
}