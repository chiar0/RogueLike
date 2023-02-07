#pragma once
#include <iostream>
#include <ncurses.h>
#include "engine.hpp"

class Bullet{
    private:
        engine* dungeon;
        int damage;
        int xLoc, yLoc;
        int direction;
        char bullet;
        char character;
        bool isEnemy;
        

    public:
        Bullet(engine *dungeon, int damage, int xLoc, int yLoc, int direction, char bullet, char character);

        void genb(int xLoc, int yLoc);          //genera il proiettile
        bool move();                            //aggiorna la posizione e controlla cosa ha colpito
        void display();                         //riposiziona il proiettile dopo averlo mosso(attualmente non in uso)
        
        //getter
        int getx();                             
        int gety();
        char getProjectile();
        char getChar();
        int dir();
        bool getIsEnemy();
        int getDamage();

};