#include <iostream>
#include "game.h"

int main() {

    Game game;

    while(game.winRunning()) {
        //update
        game.update();

        //render
        game.render();
    }

    return 0;
}