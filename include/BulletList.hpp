#pragma once

#include "engine.hpp"
#include "Bullet.hpp"

struct bullets{
            Bullet      bullet;
            bullets     *next;
            bullets     *prev;

            bullets(const Bullet& b, bullets* n, bullets* p) : bullet(b), next(n), prev(p) {}

            int length() {
                int i = 0;
                bullets *tmp = this;
                while(tmp != NULL) {
                    i+=1;
                    tmp = tmp->next;
                }
                return i;
            }
        };  typedef bullets* Bul;

class BulletList{
    protected:
        engine* dungeon;
        Bul bulletHead;
        int EnemyDamage;
        int PlayerDamage;
        int prjct;

    public:
        BulletList();
        BulletList(engine* dungeon);
        void addBullet(int damage, int direction, int positionX, int positionY, char character, char projectile, bool isEnemy);
        bullets* removeBullet(bullets* bullet);
        bool hit();
        void update();
        bullets* getBulletHead();
        void display();
        int listLength();
        int isHit(int directionX, int directionY);
        void addToList(Bullet bullet);

};