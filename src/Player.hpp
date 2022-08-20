
#ifndef _PLAYER_H_
#define _PLAYER_H_


#include <iostream>
#include <ncurses.h>

class Player{
    private:
        int xLoc, yLoc, xMax, yMax;
        char character;
        WINDOW* win;

    public:
        Player(WINDOW* win, int y, int x, char c);

        void mvup();
        void mvdown();
        void mvleft();
        void mvright();
        int getmv();
        void display();
        int getx();
        int gety();  


        void moveLeft();  
};


#endif