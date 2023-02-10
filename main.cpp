#include "main.hpp"

int main() {

    menu* gameMenu = new menu();
    while(getch() != 'x'){
        gameMenu->display();
    }
    Game* game = new Game();
    game->gameLoop();
    endwin();
    delete game;

    return 0;
}