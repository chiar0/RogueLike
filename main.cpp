#include "main.hpp"


/*
void controller(engine *dungeon, Player p, List l) { //gestisce l'input
    char ch = ' ';
    while(ch != 'x') {
        ch = p.update();
        l.updateAll(p.getPositionX(), p.getPositionY());
    }
}
*/

int main() {
    /*
    
    engine *dungeon=new engine();
    
    int x = dungeon->random_clear_point().x;
    int y = dungeon->random_clear_point().y;
    Player p(x, y, 100, 10, dungeon, '@');
    p.display();
    List l(4, 4, dungeon);
    dungeon->refresh_dungeon();

    while (true) {
        controller(dungeon, p, l);
        break;
    }
    */
    Game* game = new Game();
    game->gameLoop();
    endwin();

    return 0;
}