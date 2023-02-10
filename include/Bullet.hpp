#pragma once
#include <iostream>
#include <ncurses.h>
#include "engine.hpp"

class Bullet{
    private:
        engine* dungeon = NULL;
        int damage;
        int locationX, locationY;
        int direction;
        char bullet;
        char character;
        bool isEnemy;
        

    public:
        Bullet(engine *dungeon, int damage, int locationX, int locationY, int direction, char bullet, char character);
        bool move();                //aggiorna la posizione e controlla cosa ha colpito
        void display();             //riposiziona il proiettile dopo averlo mosso
        void hideBullet();          //nasconde il proiettile
        
        //getter
        int getx();                             
        int gety();
        char getProjectile();
        char getCharacter();
        int getDirection();
        bool getIsEnemy();
        int getDamage();

};