#include "../header/game.h"

int main() {
    try {
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
    catch (const std::exception& e) {
        std::cerr << "Failed to initialize the game: " << e.what() << std::endl; 
        return EXIT_FAILURE; 
    }

    return EXIT_SUCCESS;
}