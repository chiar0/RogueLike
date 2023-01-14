#include "main.hpp"

void controller(engine *dungeon) { //gestisce l'input
    switch (int ch = getch()) { //legge un carattere
        case KEY_UP: //se viene premuto il tasto freccia su
            dungeon->next_level(); //passa al livello successivo
            break;
        case KEY_DOWN: //se viene premuto il tasto freccia giù
            dungeon->prev_level(); //passa al livello precedente
            break;
        case 'q':
            dungeon->life_update(-1); //decrementa la vita
            dungeon->write_char(dungeon->random_clear_point(), 'q'); //scrive un q in un punto casuale libero
            dungeon->refresh_dungeon(); //aggiorna la finestra del dungeon
            break;
    }
}

int main() {
    engine *dungeon=new engine();

    while (true) {
        controller(dungeon);
    }
    return 0;
}