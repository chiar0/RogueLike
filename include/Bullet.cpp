#include "Bullet.hpp"

Bullet::Bullet(engine *dungeon, int damage, int xLoc, int yLoc, int direction, char bullet, char character){
    this->dungeon = dungeon;
    this->damage = damage;
    this->xLoc = xLoc;
    this->yLoc = yLoc;
    this->direction = direction;
    this->bullet = bullet;
    this->character = character;
    this->isEnemy = isEnemy;
}

void Bullet::genb(int xLoc, int yLoc){
    this->xLoc = xLoc;
    this->yLoc = yLoc;
}

bool Bullet::move(){
    bool alive = true;
    //muovo in base alla direzione con la quale è stato generato il proiettile
    switch(this->direction){
        case 1: //up
            yLoc = yLoc - 1;
        break;
        case 2: //left
            xLoc = xLoc - 1;
        break;
        case 3: //down
            yLoc = yLoc + 1;
        break;
        case 4: //right
            xLoc = xLoc + 1;
        break;

        default:
            return false;
        break;
    }
    //verifico se effettivamente il proiettile si muove porcoddio
    //dungeon->write_char(dungeon->random_clear_point(), 'q');
    //dungeon->refresh_dungeon();
    
    //verifico se sulla mappa è presente qualcosa su quella posiizone
    display::point p{yLoc, xLoc};
    char mapChar = mvwinch(dungeon->retrive_dungeon(), yLoc, xLoc);
    if(mapChar == ' ' || mapChar == '+'){
            return true;
        }
        else{
            return false;
        }
}

void Bullet::display(){
    wmove(dungeon->retrive_dungeon(), this->yLoc, this->xLoc);
    waddch(dungeon->retrive_dungeon(), '+');
    //mvwprintw(win, 0, 0, "%d %d", yLoc, xLoc);
    //mvwprintw(this->win, this->yLoc, this->xLoc, "%c", this->bullet);
}



char Bullet::getProjectile(){
    return this->bullet;
}

char Bullet::getChar(){
    return this->character;
}


int Bullet::dir(){
    return this->direction;
}

int Bullet::getx(){
    return this->xLoc;
}

int Bullet::gety(){
    return this->yLoc;
}

bool Bullet::getIsEnemy(){
    return this->isEnemy;
}

int Bullet::getDamage(){
    return this->damage;
}

