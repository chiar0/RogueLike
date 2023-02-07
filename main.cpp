#include "main.hpp"

void controller(engine *dungeon, Player p) { //gestisce l'input
    char ch = ' ';
    while(ch != 'x') {
        ch = p.update();
    }
}

int main() {
    
    engine *dungeon=new engine();
    
    int x = dungeon->random_clear_point().x;
    int y = dungeon->random_clear_point().y;
    Player p(x, y, 100, 10, dungeon);
    p.display();
    dungeon->refresh_dungeon();

    while (true) {
        controller(dungeon, p);
        break;
    }
    return 0;
}