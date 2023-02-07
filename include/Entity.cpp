#include "Entity.hpp"

    Entity::Entity(){}

    // costruttore
    Entity::Entity(int positionX, int positionY, int HP, int damage, engine* dungeon, char character, BulletList* bulletsList){
        this->positionX = positionX;
        this->positionY = positionY;
        this->HP = HP;
        this->damage = damage;
        this->dungeon = dungeon;
        this->character = character;
        this-> xMax = getmaxx(this->dungeon->retrive_dungeon());
        this-> yMax = getmaxy(this->dungeon->retrive_dungeon());
        this->bulletsList = bulletsList;
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
        //wmove(dungeon->retrive_dungeon(), this->positionY, this->positionX);
        //waddch(dungeon->retrive_dungeon(), character);
        display::point p{this->positionY, this->positionX};
        this->dungeon->write_char(p, this->character);
        //dungeon->refresh_dungeon();
    };

    // metodo che aggiorna la matrice 3x3 che contiene i caratteri nelle caselle adiacenti a quella in cui si trova l'entità
    // viene lanciata per ogni entità per ogni update()
    void Entity::updateNearby(){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                nearby[i][j] = mvwinch(dungeon->retrive_dungeon(), getPositionY() + i - 1, getPositionX() + j - 1);
            }
        }
    }

    // metodi per i movimenti, in ognuno di essi sono gestiti i controlli per evitare che l'entità esca dalla finestra
    // e per evitare che si muova su altre entità
    //ho messo le funzioni di fabio al posto di quelle di libreria
    void Entity::moveUp(){
        wmove(dungeon->retrive_dungeon(), positionY, positionX);
        if (nearby[0][1] == ' ') {
            //waddch(dungeon->retrive_dungeon(), ' ');
            display::point p{this->positionY, this->positionX};
            this->dungeon->write_char(p, ' ');
            if (positionY < 1) { positionY = 1; }
            else { positionY = positionY - 1; } 
        }
        display();
    }
    void Entity::moveDown(){
        wmove(dungeon->retrive_dungeon(), positionY, positionX);
        if (nearby[2][1] == ' ') {
            //waddch(dungeon->retrive_dungeon(), ' ');
            display::point p{this->positionY, this->positionX};
            this->dungeon->write_char(p, ' ');
            if (positionY > yMax - 2) { positionY = yMax - 2; }
            else { positionY = positionY + 1; }
        }
        display();
    }
    void Entity::moveLeft(){
        wmove(dungeon->retrive_dungeon(), positionY, positionX);
        if (nearby[1][0] == ' ') {
            //waddch(dungeon->retrive_dungeon(), ' ');
            display::point p{this->positionY, this->positionX};
            this->dungeon->write_char(p, ' ');
            if (positionX < 1) { positionX = 1; }
            else { positionX = positionX - 1; }
        }
        display();
    }
    void Entity::moveRight(){
        wmove(dungeon->retrive_dungeon(), positionY, positionX);
        if (nearby[1][2] == ' ') {
            //waddch(dungeon->retrive_dungeon(), ' ');
            display::point p{this->positionY, this->positionX};
            this->dungeon->write_char(p, ' ');
            if (positionX > xMax - 2) { positionX = xMax - 2; }
            else { positionX = positionX + 1; }
        }
        display();
    }

    void Entity::isDead() {
        if (HP <= 0) {
            wmove(dungeon->retrive_dungeon(), positionY, positionX);
            waddch(dungeon->retrive_dungeon(), ' ');
        }
        display();
    }


    /*
    funzione per la gestione dei proiettili quando sono gestiti dalle entità
    void Entity::shoot(int direction){
        
        Bullet bul(this->dungeon, this->damage, positionX, positionY, direction, '+', character);
        bullets *tmp = new bullets(bul, NULL, NULL);
        if (first == NULL){
            first = tmp;
            last = tmp;
        }
        else{
            tmp->next = first;
            first = tmp;
        
        bullets->addBullet(dungeon, damage, direction, positionX, positionY, character, '+', false);
    };

    
    void Entity::updateBullet(){
        Bul aux = first, prev = first;
        bool alive = false;

        prev = first;

        if(first != NULL){
            while(aux != NULL){
                mvwprintw(dungeon->retrive_dungeon(), aux->bullet.gety(), aux->bullet.getx(), "%c", ' ');
                alive = aux->bullet.move();

                if(alive == true){
                    mvwprintw(dungeon->retrive_dungeon(), aux->bullet.gety(), aux->bullet.getx(), "%c", aux->bullet.getChar());
                    //aux->bullet.display();
                    prev = aux;
                    aux = aux->next;
                }

                else{
                    if(aux == first && first->next == NULL){
                        delete aux;
                        first = NULL;
                        aux = NULL; 
                    }
                    else if(aux == first && first->next != NULL){
                        first = first->next;
                        delete aux;
                        aux = NULL;
                        aux = first;
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
        display();
    }; 
    */

    void Entity::isHit(int bulletX, int bulletY, int dmg){
        if(bulletX == this->positionX && bulletY == this->positionY)
            setHP(dmg);
    }

    void Entity::addBullets(int direction, bool isEnemy){
        this->bulletsList->addBullet(damage, direction, positionX, positionY, character, '+', isEnemy);
    }