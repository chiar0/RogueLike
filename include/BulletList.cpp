#include "BulletList.hpp"

BulletList::BulletList() {
  this->bulletHead = NULL;
  this->dungeon = NULL;
}


BulletList::BulletList(engine* dungeon){
    this->bulletHead = NULL;
    this->dungeon = dungeon;
}

void BulletList::addBullet(int damage, int direction, int positionX, int positionY, char character, char projectile, bool isEnemy){
    Bullet bul(this->dungeon, damage, positionX, positionY, direction, projectile, character);
    addToList(bul);
}


void BulletList::update(){
    bullets* aux = this->bulletHead;
    bullets* prev = this->bulletHead;
    bool alive;


    if(bulletHead != NULL){
        while(aux != NULL){
            display::point p{aux->bullet.gety(), aux->bullet.getx()};
            dungeon->write_char(p, ' ');
            alive = aux->bullet.move();

            char mapChar = mvwinch(dungeon->retrive_dungeon(), aux->bullet.gety(), aux->bullet.getx());
            if(alive == true){
                display::point p{aux->bullet.gety(), aux->bullet.getx()};
                dungeon->write_char(p, aux->bullet.getChar());
                aux->bullet.display();
                prev = aux;
                aux->next;
            }
            else{
                if(aux == bulletHead && bulletHead->next == NULL){
                        delete aux;
                        bulletHead = NULL;
                        aux = NULL; 
                    }
                    else if(aux == bulletHead && bulletHead->next != NULL){
                        bulletHead = bulletHead->next;
                        delete aux;
                        aux = NULL;
                        aux = bulletHead;
                    }
                    else{
                        prev->next = aux->next;
                        delete aux;
                        aux = NULL;
                        aux = prev->next;
                }
            }
            //dungeon->refresh_dungeon();
        }
    }
}

bullets* BulletList::removeBullet(bullets* bullet){
    bullets* aux;
    bullets* tmp;
    /*
    if(bullet != bulletHead){
        bullets* aux = bullet->prev;
        aux->next = bullet->next;
        aux = bullet;
        bullet = bullet->next;
        bullet->prev = aux->prev;
        delete aux;
    }
    else{
        bullets* aux = bulletHead;
        bulletHead = bulletHead->next;
        bulletHead->prev = NULL;
        delete aux;
        bulletHead = NULL;
        aux = ;
    }
    */

    if(bullet != bulletHead){
        aux = bullet->prev;
        aux->next = bullet->next;
        aux = bullet;
        bullet->prev = aux->prev;
        delete aux;
    }
    else{
        delete bulletHead;
        bulletHead = NULL;
        bullet = NULL;
    }
    return bullet;
}

bullets* BulletList::getBulletHead(){
    return bulletHead;
}

void BulletList::display(){
    bullets* aux = this->bulletHead;


    if(bulletHead != NULL){
        while(aux != NULL){
            display::point p{aux->bullet.gety(), aux->bullet.getx()};
            this->dungeon->write_char(p, aux->bullet.getChar());
            if(mvwinch(dungeon->retrive_dungeon(), aux->bullet.gety(), aux->bullet.getx()) == '+'){
                dungeon->write_char(dungeon->random_clear_point(), 'q');
                dungeon->refresh_dungeon();
            }
            aux = aux->next;
        }
    }
    //dungeon->refresh_dungeon();
}

int BulletList::listLength(){
    return bulletHead->length();
}

int BulletList::isHit(int directionX, int directionY){
    bullets* aux = this->bulletHead;
    bullets* prev = this->bulletHead;
    bool alive;
    int damageTaken = 0;


    if(bulletHead != NULL){
        while(aux != NULL){
            int bulletX = aux->bullet.getx();
            int bulletY = aux->bullet.gety();

            //char mapChar = mvwinch(dungeon->retrive_dungeon(), aux->bullet.gety(), aux->bullet.getx());
            if(bulletX == directionX && directionY == bulletY){
                damageTaken += aux->bullet.getDamage();
                if(aux == bulletHead && bulletHead->next == NULL){
                    delete aux;
                    bulletHead = NULL;
                    aux = NULL; 
                }
                else if(aux == bulletHead && bulletHead->next != NULL){
                    bulletHead = bulletHead->next;
                    delete aux;
                    aux = NULL;
                    aux = bulletHead;
                }
                else{
                    prev->next = aux->next;
                    delete aux;
                    aux = NULL;
                    aux = prev->next;
                }
            }
            else{
                prev = aux;
                aux->next;
            }
        }
        //dungeon->refresh_dungeon();
    }
    return damageTaken;
}

void BulletList::addToList(Bullet bullet){
    //bullets* tmp = new bullets(bullet, NULL, NULL);
    bullets *tmp = (bullets*) malloc(sizeof(bullets));
    tmp->bullet = bullet;
    tmp->next = NULL;
    tmp->prev = NULL;
    if(bulletHead != NULL){
        tmp->next = bulletHead;
        bulletHead->prev = tmp;
        bulletHead = tmp;
        
    }
    else{
        bulletHead = tmp;
    }
}


