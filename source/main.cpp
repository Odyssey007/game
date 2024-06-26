#include "../header/game.h"

int main() {
    Game game;
    while(game.winRunning()) {
        DeltaTime::getInstace()->restart();
        //update frame
        game.update();
        //render the new update
        game.render();
    }
    delete DeltaTime::getInstace();
}