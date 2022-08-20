
#ifndef _ENEMY_HPP
#define _ENEMY_HPP

#include <iostream>
#include <ncurses.h>
#include "Player.hpp"
using namespace std;

class Enemy:public Player {

    private:
        //int x, y;

    public:
        Enemy(WINDOW* win, int y, int x, char c);
        int getmv(int x, int y);
        //void display();

};



#endif