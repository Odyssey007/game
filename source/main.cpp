#include <iostream>
#include "../header/game.h"

int main() {
    Game game;

    while(game.winRunning()) {
        //update frame
        game.update();
        //render the new update
        game.render();
    }

    return 0;
}