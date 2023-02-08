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
        Player* p;
        // List* enemies;
        engine* dungeon;

        int maxId;

        struct listOfLists {
            List list;
            listOfLists* next;
            listOfLists* prev;
            listOfLists(List l) : list(l), next(NULL), prev(NULL) {}
        };
        listOfLists* head;
        listOfLists* current;

        BulletList *bulletsList;
        
    public:
        //costruttore
        Game();
        
        int getMaxId();
        void nextList();
        void prevList();
        void newList(int nMeelee, int nRanged, engine* dungeon);

        //funzioni per la gestione del gioco
        void gameLoop();
        void shoot();
        void genEnemys(int nMeelee, int nRanged);
        void checkBullets();
        void checkMeelee();
        void checkRanged();
        void checkPlayer();

};