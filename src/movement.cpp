#include <iostream>
#include <ncurses.h>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include "Player.hpp"
#include "Enemy.hpp"

using namespace std;

int main () {
    initscr();
    noecho();
    cbreak();

    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);
    WINDOW* win = newwin(20, xMax-12, yMax-24, 5);
    box(win, 0, 0);
    refresh();
    wrefresh(win);
    keypad(win, true);
    
    Player* p = new Player(win, 3, 3, '@');
    Enemy* e = new Enemy(win , 15, 10, 'c');

    while(p->getmv()!='x'){
        p->display();
        e->getmv(p->getx(), p->gety());
        e->display();
        wrefresh(win);
    }

    
    getch();
    endwin();
    delete(win);

    return 0;
}