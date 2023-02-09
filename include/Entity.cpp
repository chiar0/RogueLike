#include "Entity.hpp"

    // costruttore
    Entity::Entity(){}

    Entity::Entity(int positionX, int positionY, int HP, int damage, engine* dungeon, BulletList* bulletslist){
        this->positionX = positionX;
        this->positionY = positionY;
        this->HP = HP;
        this->damage = damage;
        this->dungeon = dungeon;
        this->xMax = getmaxx(this->dungeon->retrive_dungeon());
        this->yMax = getmaxy(this->dungeon->retrive_dungeon());
        this->bulletsList = bulletslist;
        
    }

    // getters
    int Entity::getPositionX() { return positionX; }
    int Entity::getPositionY() { return positionY; }
    int Entity::getMaxX() { return xMax; }
    int Entity::getMaxY() { return yMax; }
    int Entity::getHP() { return HP; }
    int Entity::getDamage() { return this->damage; }
    char Entity::getCharacter() { return character; }
    char Entity::getNearby(int x, int y) { return nearby[x][y]; }

    // setters
    void Entity::setHP(int lostHPs) { HP = HP - lostHPs; }
    void Entity::setPositionX(int x) { positionX = x; }
    void Entity::setPositionY(int y) { positionY = y; }

    // metodo che stampa l'entità sulla finestra
    void Entity::display(){
        wmove(dungeon->retrive_dungeon(), positionY, positionX);
        waddch(dungeon->retrive_dungeon(), character);
    };

    // metodo che oscura l'entità dalla finestra
    void Entity::hide(){
        wmove(dungeon->retrive_dungeon(), positionY, positionX);
        waddch(dungeon->retrive_dungeon(), ' ');
    };

    // metodo che aggiorna la matrice 3x3 che contiene i caratteri nelle caselle adiacenti a quella in cui si trova l'entità
    // viene lanciata per ogni entità per ogni update()
    void Entity::updateNearby(){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                nearby[i][j] = mvwinch(dungeon->retrive_dungeon(), positionY + i - 1, positionX + j - 1);
            }
        }
    }

    // metodi per i movimenti, in ognuno di essi sono gestiti i controlli per evitare che l'entità esca dalla finestra
    // e per evitare che si muova su altre entità

    void Entity::moveUp(){
        wmove(dungeon->retrive_dungeon(), positionY, positionX);
        if (nearby[0][1] == ' ') {
            waddch(dungeon->retrive_dungeon(), ' ');
            if (positionY < 1) { positionY = 1; }
            else { positionY = positionY - 1; } 
        }
        display();
    }
    void Entity::moveDown(){
        wmove(dungeon->retrive_dungeon(), positionY, positionX);
        if (nearby[2][1] == ' ') {
            waddch(dungeon->retrive_dungeon(), ' ');
            if (positionY > yMax - 2) { positionY = yMax - 2; }
            else { positionY = positionY + 1; }
        }
        display();
    }
    void Entity::moveLeft(){
        wmove(dungeon->retrive_dungeon(), positionY, positionX);
        if (nearby[1][0] == ' ') {
            waddch(dungeon->retrive_dungeon(), ' ');
            if (positionX < 1) { positionX = 1; }
            else { positionX = positionX - 1; }
        }
        display();
    }
    void Entity::moveRight(){
        wmove(dungeon->retrive_dungeon(), positionY, positionX);
        if (nearby[1][2] == ' ') {
            waddch(dungeon->retrive_dungeon(), ' ');
            if (positionX > xMax - 2) { positionX = xMax - 2; }
            else { positionX = positionX + 1; }
        }
        display();
    }

    bool Entity::isDead() {
        bool dead = false;
        if (HP <= 0) {
            hide();
            dead = true;
        }
        return dead;
    }

    // metodo che controlla se l'entità è stata colpita da un bullet
    /*
    void Entity::isHit(int bulletX, int bulletY, int dmg){
    if(bulletX == this->positionX && bulletY == this->positionY)
        setHP(dmg);
    }
    */

    // metodo che aggiunge un bullet alla lista di proiettili
    void Entity::addBullets(int direction, bool isEnemy, int entityX, int entityY){
        this->bulletsList->addBullet(this->dungeon, this->damage, entityX, entityY, direction, this->character, (char)'+', isEnemy);
    }