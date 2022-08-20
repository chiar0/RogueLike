#include "Player.hpp"


    Player::Player(WINDOW* win, int y, int x, char c){
        this->win = win;
        yLoc = y;
        xLoc = x;
        character = c;
        getmaxyx(this->win, this->yMax, this->xMax);
        keypad(this->win, true);
    };

    void Player::moveLeft(){
        xLoc--;
    }

    int Player::getx(){
        return this->xLoc;
    }

    int Player::gety(){
        return this->yLoc;
    }

    void Player::mvup(){
        wmove(win, yLoc, xLoc);
        waddch(win, ' ');
        yLoc = yLoc-1;
        if(yLoc < 1)
            yLoc = 1;
    };

    void Player::mvdown(){
        wmove(win, yLoc, xLoc);
        waddch(win, ' ');
        yLoc += 1;
        if(yLoc > yMax-2)
            yLoc = yMax-2;
    };

    void Player::mvleft(){
        wmove(win, yLoc, xLoc);
        waddch(win, ' ');
        int tempx = xLoc;
        mvwprintw(win, 0, 10, "%d %d", xLoc, tempx);
         while(xLoc >= tempx){
            xLoc--;
        }
        if(xLoc != tempx)
            moveLeft();
        if(xLoc < 1)
            xLoc = 1;
    };

    void Player::mvright(){
        wmove(win, yLoc, xLoc);
        waddch(win, ' ');
        xLoc += 1;
        if(xLoc > xMax - 2)
            xLoc = xMax-2;
    };

    int Player::getmv(){
        int choice = wgetch(win);

        switch (choice){
        case (int)'w':
            mvup();
            break;
        case (int)'s':
            mvdown();
            break;
        case (int)'a':
            mvleft();
        case (int)'d':
            mvright();
            break;

        default:
            break;
        }
        return choice;
    };

    void Player::display(){
        wmove(win, yLoc, xLoc);
        waddch(win, character);
        mvwprintw(win, 0, 0, "%d %d", yLoc, xLoc);
    };
