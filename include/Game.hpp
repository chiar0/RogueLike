#pragma once
#include <ctime>
#include "Player.hpp"   
#include "List.hpp"
#include "BulletList.hpp"
#include "Timer.hpp"


class Game{

    private:
        //variabili per la temporizzazione e gestione del game
        int tick = 2;
        int updateCounter = 0;
        int maxId;

        //classi e liste necessarie per il programma
        WINDOW* debug;
        Player* p;
        engine* dungeon;
        Timer* enemyTimer = Timer::Instance();

        struct listOfLists {
            BulletList* bulletsList;
            List* list;
            listOfLists* next;
            listOfLists* prev;
            listOfLists(BulletList* b, List* l) : bulletsList(b), list(l), next(NULL), prev(NULL) {}
        };
        listOfLists* head;          //testa alla listOfList
        listOfLists* current;       //puntatore alla stanza corrente
        
    public:
        //costruttore
        Game();

        //get
        int getMaxId();

        //gestione della lista
        void nextList(int nMeelee, int nRanged, engine *dungeon);   //cambia la lista in caso di passaggio al livello successivo
        void prevList();                                            //cambia la lista in caso di ritorno al livello precedente
        void newList(int nMeelee, int nRanged, engine* dungeon);    //genera una nuova lista per il livello successivo


        //funzioni per la gestione del gioco
        void gameLoop();                //gestisce il gioco e il tempo
        void shoot();                   //viene verificato se i proiettili hanno colpito delle entità
        void checkBullets();            //funzione principale per la verifica delle entità
        void checkMeelee();             //verifica per i meelee             
        void checkRanged();             //verifica per i ranged
        void checkPlayer();             //verifica per il giocatore
        void updatePlayer(int move);    //gestisce lo spostamento del giocatore nel livello e tra di essi

};