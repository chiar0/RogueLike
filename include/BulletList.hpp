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
        void startDungeon(engine* dungeon);
        BulletList();
        BulletList(engine* dungeon);
        
        bullets* removeBullet(bullets* bullet);
        bullets* getBulletHead();

        void addBullet(engine* dungeon, int damage, int positionX, int positionY, int direction, char character, char projectile, bool isEnemy);
        void addToList(Bullet* b);

        //bool hit();
        void update();
        void display();
        //int listLength();
        int isHit(int directionX, int directionY, char character);
        
        void resetList();
        void hideAll();

};