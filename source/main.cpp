#include "../header/game.h"

int main() {
    Game game;
    while(game.winRunning()) {
        DeltaTime::getInstance()->restart();
        game.update(); //update frame
        game.render(); //render the new update
    }
    delete DeltaTime::getInstance();
}