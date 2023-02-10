#include "main.hpp"

int main() {
    Game* game = new Game();
    game->gameLoop();
    endwin();
    delete game;

    return 0;
}