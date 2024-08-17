#include "../header/battle/game.h"
#include "../header/game/window.h"

int main() {
    Game game;
    //Screen game; 
    while(game.winRunning()) {
        DeltaTime::getInstance()->restart();
        game.update(); //update frame
        game.render(); //render the new update
    }
    delete DeltaTime::getInstance();
}