#include "Enemy.hpp"

Enemy::Enemy(WINDOW* win, int x, int y, char c):Player(win, x, y, c){};

int Enemy::getmv(int x, int y){
    int diffX, diffY;

    diffX = Player::getx() - x;
    diffY = Player::gety() - y;



    if(abs(diffX) > abs(diffY)){
        if(diffX < 0)
            Player::mvright();
        else
            Player::mvleft();
    }
    else if(abs(diffX) < abs(diffY)){
        if(diffY < 0)
            Player::mvdown();
        else
            Player::mvup();
    }

    return 1;

}