#pragma once
#include <ctime>
#include "Player.hpp"
#include "List.hpp"
#include "BulletList.hpp"


class Game{

    private:
        //variabili per la temporizzazione
        int tick = 2;
        int updateCounter = 0;

        //classi e liste necessarie per il programma
        WINDOW* debug;
        Player p;
        List* enemies;
        engine* dungeon;

        //
        BulletList bulletsList;
        
    public:
        //costruttore
        Game();
        
        //funzioni per la gestione del gioco
        void gameLoop();
        void shoot();
        void genEnemys(int nMeelee, int nRanged);
        void checkBullets();
        void checkMeelee();
        void checkRanged();
        void checkPlayer();
        void checkPlayerOnly();

};