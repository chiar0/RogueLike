#include "Bullet.hpp"

Bullet::Bullet(engine* dungeon, int damage, int locationX, int locationY, int direction, char bullet, char character){
    this->dungeon = dungeon;
    this->damage = damage;
    this->locationX = locationX;
    this->locationY = locationY;
    this->direction = direction;
    this->bullet = bullet;
    this->character = character;
    this->isEnemy = isEnemy;
}

bool Bullet::move(){
    bool alive = true;

    //muovo in base alla direzione con la quale è stato generato il proiettile
    switch(direction){
        case 1: //up
            locationY = locationY - 1;
        break;
        case 2: //left
            locationX = locationX - 1;
        break;
        case 3: //down
            locationY = locationY + 1;
        break;
        case 4: //right
            locationX = locationX + 1;
        break;

        default:
            return false;
        break;
    }
    
    //verifico se sulla mappa è presente qualcosa su quella posiizone
    char mapChar = mvwinch(dungeon->retrive_dungeon(), locationY, locationX);
    if(mapChar == ' ' || mapChar == '+' || mapChar == character){
        return true;
    }
    else{
        return false;
    } 
}

void Bullet::display(){
    wmove(dungeon->retrive_dungeon(), this->locationY, this->locationX);
    waddch(dungeon->retrive_dungeon(), '+');
}

void Bullet::hideBullet(){
    wmove(dungeon->retrive_dungeon(), this->locationY, this->locationX);
    waddch(dungeon->retrive_dungeon(), ' ');
}

char Bullet::getProjectile(){
    return this->bullet;
}

char Bullet::getCharacter(){
    return this->character;
}


int Bullet::getDirection(){
    return this->direction;
}

int Bullet::getx(){
    return this->locationX;
}

int Bullet::gety(){
    return this->locationY;
}

bool Bullet::getIsEnemy(){
    return this->isEnemy;
}

int Bullet::getDamage(){
    return this->damage;
}

