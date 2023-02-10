#include "BulletList.hpp"

//costuttore di default della classe
BulletList::BulletList(){
    this->bulletHead = NULL;
    this->dungeon = NULL;
}

//costruttore di default della lista
bullets::bullets(){
    bullet = NULL;
    prev = NULL;
    next = NULL;
}

BulletList::BulletList(engine* dungeon){
    bullets* tmp = NULL;
    this->bulletHead = NULL;
    this->dungeon = dungeon;
}

void BulletList::addBullet(engine* dun, int damage, int positionX, int positionY, int direction, char character, char projectile, bool isEnemy){
    Bullet* bul = new Bullet(dun, damage, positionX, positionY, direction, projectile, character);
    addToList(bul);
}

void BulletList::startDungeon(engine* dungeon){
    this->dungeon = dungeon;
}

void BulletList::update(){
    bullets* aux = this->bulletHead;
    bullets* prev = this->bulletHead;
    bool alive;
    char mapChar;
    if(bulletHead != NULL){
        while(aux != NULL){
            display::point p{aux->bullet->gety(), aux->bullet->getx()};
            mapChar = mvwinch(dungeon->retrive_dungeon(), aux->bullet->gety(), aux->bullet->getx());
            //aggiorno il vecchio punto del proiettile
            if(mapChar == ' ' || mapChar == '+'){
                dungeon->write_char(p, ' ');
            }
            alive = aux->bullet->move();
            char mapChar = mvwinch(dungeon->retrive_dungeon(), aux->bullet->gety(), aux->bullet->getx());
            //verifico se il proiettile è da tenere
            if(alive == true || mapChar == '@' || mapChar == 'R' || mapChar == 'M'){
                prev = aux;
                aux = aux->next;
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
        }
    }
}

//rimozione di un proiettile dalla lista
bullets* BulletList::removeBullet(bullets* bullet){
    bullets* aux;
    bullets* tmp;
    display::point p{aux->bullet->gety(), aux->bullet->getx()};
    dungeon->write_char(p, ' ');

    if(bullet != bulletHead){
        aux = bullet->prev;
        aux->next = bullet->next;
        aux = bullet;
        bullet->prev = aux->prev;
        delete aux->bullet;
        delete aux;
        aux = NULL;
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
    bullets* aux = bulletHead;
    if(bulletHead != NULL){
        while(aux != NULL){
            aux->bullet->display();
            if(mvwinch(dungeon->retrive_dungeon(), aux->bullet->gety(), aux->bullet->getx()) == '+'){
            }
            aux = aux->next;
        }
    }
    dungeon->refresh_dungeon();
}

int BulletList::isHit(int directionX, int directionY, char character){
    bullets* aux = NULL;
    aux = bulletHead;
    bullets* prev = bulletHead;
    bool alive;
    int damageTaken = 0;
    int bulletX;
    int bulletY;
    
    while(aux != NULL){
        bulletX = aux->bullet->getx();
        bulletY = aux->bullet->gety();
        //verifico se il proiettile ha colpito l'entità
        if(bulletX == directionX && directionY == bulletY && character != aux->bullet->getCharacter()){
            damageTaken += aux->bullet->getDamage();
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
            aux = aux->next;
            //3;
        }
    }

    return damageTaken;
}

//aggiungo un proiettile alla lista
void BulletList::addToList(Bullet* bul){
    bullets* tmp = new bullets();
    tmp->bullet = bul;
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


void BulletList::resetList(){
    hideAll(); 
    if(bulletHead != NULL){
        if(bulletHead->next != NULL){
            
            bullets* aux = bulletHead->next; 
            bullets* tmp = NULL;
             
            while(aux->next != NULL){
                tmp = aux;
                aux = aux->next;
                delete tmp;
            }
            delete aux->next;
        }      
        this->bulletHead = NULL;  
    }  
}

void BulletList::hideAll(){
    if(this->bulletHead != NULL){
        bullets* tmp = bulletHead;
        while(tmp != NULL){
            tmp->bullet->hideBullet();
            tmp = tmp->next;
        }
    }
}


