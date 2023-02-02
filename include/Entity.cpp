#include "Entity.hpp"

    // costruttore
    Entity::Entity(int positionX, int positionY, int room, int HP, int damage, engine* dungeon, char character){
        this->positionX = positionX;
        this->positionY = positionY;
        this->HP = HP;
        this->damage = damage;
        this->dungeon = dungeon;
        this->window = this->dungeon->retrive_dungeon();
        this->character = character;
        this-> xMax = getmaxx(this->window);
        this-> yMax = getmaxy(this->window);
    }

    // getters
    int Entity::getPositionX() { return positionX; }
    int Entity::getPositionY() { return positionY; }
    int Entity::getMaxX() { return xMax; }
    int Entity::getMaxY() { return yMax; }
    int Entity::getHP() { return HP; }
    int Entity::getDamage() { return this->damage; }
    WINDOW* Entity::getWindow() { return window; }
    char Entity::getCharacter() { return character; }
    char Entity::getNearby(int x, int y) { return nearby[x][y]; }

    // setters
    void Entity::setHP(int lostHPs) { HP = HP - lostHPs; }
    void Entity::setPositionX(int x) { positionX = x; }
    void Entity::setPositionY(int y) { positionY = y; }

    // metodo che stampa l'entità sulla finestra
    void Entity::display(){
        wmove(window, getPositionY(), getPositionX());
        waddch(window, character);
    };

    // metodo che aggiorna la matrice 3x3 che contiene i caratteri nelle caselle adiacenti a quella in cui si trova l'entità
    // viene lanciata per ogni entità per ogni update()
    void Entity::updateNearby(){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                nearby[i][j] = mvwinch(window, getPositionY() + i - 1, getPositionX() + j - 1);
            }
        }
    }

    // metodi per i movimenti, in ognuno di essi sono gestiti i controlli per evitare che l'entità esca dalla finestra
    // e per evitare che si muova su altre entità

    void Entity::moveUp(){
        wmove(window, positionY, positionX);
        if (nearby[0][1] == ' ') {
            waddch(window, ' ');
            if (positionY < 1) { positionY = 1; }
            else { positionY = positionY - 1; } 
        }
        display();
    }
    void Entity::moveDown(){
        wmove(window, positionY, positionX);
        if (nearby[2][1] == ' ') {
            waddch(window, ' ');
            if (positionY > yMax - 2) { positionY = yMax - 2; }
            else { positionY = positionY + 1; }
        }
        display();
    }
    void Entity::moveLeft(){
        wmove(window, positionY, positionX);
        if (nearby[1][0] == ' ') {
            waddch(window, ' ');
            if (positionX < 1) { positionX = 1; }
            else { positionX = positionX - 1; }
        }
        display();
    }
    void Entity::moveRight(){
        wmove(window, positionY, positionX);
        if (nearby[1][2] == ' ') {
            waddch(window, ' ');
            if (positionX > xMax - 2) { positionX = xMax - 2; }
            else { positionX = positionX + 1; }
        }
        display();
    }

    void Entity::isDead() {
        if (HP <= 0) {
            wmove(window, positionY, positionX);
            waddch(window, ' ');
        }
        display();
    }