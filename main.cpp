#include "main.hpp"

int main() {

    menu* gameMenu = new menu();
    Game* game = new Game();
    game->gameLoop();
    endwin();
    delete game;

    return 0;
}