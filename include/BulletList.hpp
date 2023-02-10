#pragma once

#include "engine.hpp"
#include "Bullet.hpp"

struct bullets{
    Bullet      *bullet;
    bullets     *next;
    bullets     *prev;

    bullets();
    bullets(Bullet* b, bullets* n, bullets* p) : bullet(b), next(n), prev(p) {}
    
};  typedef bullets* Bul;

class BulletList{
    protected:
        engine* dungeon;
        bullets* bulletHead;
        int EnemyDamage;
        int PlayerDamage;
        int prjct;

    public:
        BulletList();                               //costruttore di defeault
        BulletList(engine* dungeon);                //costruttore
        void startDungeon(engine* dungeon);         //setter del dungeon
        
        bullets* removeBullet(bullets* bullet);     //rimuove un bullet dalla lista
        bullets* getBulletHead();                   //getter della testa della lista

        //funzioni per l'aggiunta di un proiettile nella lista
        void addBullet(engine* dungeon, int damage, int positionX, int positionY, int direction, char character, char projectile, bool isEnemy);
        void addToList(Bullet* b);

        void update();                                              //aggiornamento delle posizioni di tutti i proiettili
        void display();                                             //display di tutti i proiettili 
        int isHit(int directionX, int directionY, char character);  //verifica se un proiettile ha colpito tutti i nemici
        
        void resetList();                                           //elimina tutti gli elementi della lista
        void hideAll();                                             //nasconde tutti i proiettili

};