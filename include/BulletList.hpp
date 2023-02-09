#pragma once

#include "engine.hpp"
#include "Bullet.hpp"

struct bullets{
    Bullet      *bullet;
    bullets     *next;
    bullets     *prev;

    bullets();
    bullets(Bullet* b, bullets* n, bullets* p) : bullet(b), next(n), prev(p) {}

    int length() {
        int i = 0;
        bullets *tmp = this;
        while(tmp != NULL && tmp->next != NULL) {
            i+=1;
            tmp = tmp->next;
        }
        return i;
    }
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
        void addBullet(engine* dungeon, int damage, int positionX, int positionY, int direction, char character, char projectile, bool isEnemy);
        bullets* removeBullet(bullets* bullet);
        bool hit();
        void update();
        bullets* getBulletHead();
        void display();
        int listLength();
        int isHit(int directionX, int directionY, char character);
        void addToList(Bullet* b);
        void resetList();

};