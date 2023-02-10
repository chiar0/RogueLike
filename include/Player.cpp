#include "Player.hpp"

    Player::Player():Entity() {}

    Player::Player(int positionX, int positionY, int HP, int damage, engine* dungeon, BulletList* bulletsList)
    :Entity(positionX, positionY, HP, damage, dungeon, bulletsList) {
        this->score = 0;
        this->range = 4;
        this->collectedArtifacts = 0;
        this->bulletsRemaining = 0;
        this->character = '@';
        updateNearby();
    }

    // getters
    int Player::getRange() { return range; }
    int Player::getScore() { return score; }
    int Player::getCollectedArtifacts() {return collectedArtifacts; }
    int Player::getCollectedPowerUps() {return collectedPowerUps; }

    // setters
    void Player::setRange(int increase) { range += increase; }
    void Player::setScore(int increase) { score += increase; }
    void Player::setCollectedArtifacts() { collectedArtifacts += 1; }
    void Player::setCollectedPowerUps() { collectedPowerUps += 1; }
    void Player::powerUpDamage(int increase) { damage += increase; }
    void Player::powerUpHP(int increase) { HP += increase; }

    // metodi per il movimento:
    // cotrolla se la casella in cui si vuole andare è vuota (con la matrice di adiacenze) oppure con un proiettile,
    // se questo si verifica allora si sposta
    // se si è arrivati alla fine della stanza si chiama la funzione di cambio stanza con la direzione corrispondente

    int Player::moveUp() {
        int flag = 0;
        if (nearby[0][1] == ' ' || nearby[0][1] == '+' || nearby[0][1] == '#') {
            hide();
            positionY = positionY - 1;
        } else if (nearby[0][1] == 'a' ) {
            hide();
            dungeon->clear_exit();
            positionY = positionY - 1;
            setCollectedArtifacts();
        } else if (nearby[0][1] == 'p') {
            hide();
            positionY = positionY - 1;
            setCollectedPowerUps();
            int r = rand() % 2;
            if (r == 0) {
                powerUpDamage(3);
            } else {
                powerUpHP(10);
            }
        }
        if (positionY == 0) { flag = changeRoom(0); }
        return flag;
    }

    int Player::moveDown() {
        int flag = 0;
        if (nearby[2][1] == ' ' || nearby[2][1] == '+' || nearby[2][1] == '#') {
            hide();
            positionY = positionY + 1;
        } else if (nearby[2][1] == 'a') {
            hide();
            dungeon->clear_exit();
            positionY = positionY + 1;
            setCollectedArtifacts();
        } else if (nearby[2][1] == 'p') {
            hide();
            positionY = positionY + 1;
            setCollectedPowerUps();
            int r = rand() % 2;
            if (r == 0) {
                powerUpDamage(3);
            } else {
                powerUpHP(10);
            }
        }
        if (positionY == yMax-1) { flag = changeRoom(1); }
        return flag;
    }

    int Player::moveLeft() {
        int flag = 0;
        if (nearby[1][0] == ' ' || nearby[1][0] == '+'|| nearby[1][0] == '#') {
            hide();
            positionX = positionX - 1;
        } else if (nearby[1][0] == 'a') {
            hide();
            dungeon->clear_exit();
            positionX = positionX - 1;
            setCollectedArtifacts();
        } else if (nearby[1][0] == 'p') {
            hide();
            positionX = positionX - 1;
            setCollectedPowerUps();
            int r = rand() % 2;
            if (r == 0) {
                powerUpDamage(3);
            } else {
                powerUpHP(10);
            }
        }
        if (positionX == 0) { flag = changeRoom(2); }
        return flag;
    }

    int Player::moveRight() {
        int flag = 0;
        if (nearby[1][2] == ' ' || nearby[1][2] == '+' || nearby[1][2] == '#') {
            hide();   
            positionX = positionX + 1;
        } else if (nearby[1][2] == 'a') {
            hide();
            dungeon->clear_exit();
            positionX = positionX + 1;
            setCollectedArtifacts();
        } else if (nearby[1][2] == 'p') {
            hide();
            positionX = positionX + 1;
            setCollectedPowerUps();
            int r = rand() % 2;
            if (r == 0) {
                powerUpDamage(3);
            } else {
                powerUpHP(10);
            }
        }
        if (positionX == xMax-1) { flag = changeRoom(3); }
        return flag;
    }

    void Player::shoot(int direction){
        Entity::addBullets(direction, false, Entity::getPositionX(), Entity::getPositionY());
    }


    // metodo per impostare il puntatore alla lista di nemici corrente
    // non effettuo il controllo se la lista esiste perchè nella head c'è sempre una lista di nemici

    // metodo per cambiare stanza
    // se la direction corrisponde al campo NSWE di un'uscita/entrata, allora a seconda di dove si sta cercando di entrare
    // la flag assume valore di 1 (uscita) o 2 (entrata)
  
    int Player::changeRoom(int direction) {

        int entry_NSWE = dungeon->retrive_entry_NSWE();
        int exit_NSWE = dungeon->retrive_exit_NSWE();
        int flag;

        if (direction == exit_NSWE) { flag = 1; }
        else if (direction == entry_NSWE) { flag = 2; }

        return flag;

    }

    // metodo invocato quando viene sconfitto un nemico e si aggiorna il punteggio
    void Player::defeatedEnemy(bool isBoss) {
        if (isBoss) { setScore(1500); }
        else { setScore(500); }
    }
 
    // update si occupa di modificare lo stato (come posizione, matrice delle adiacenze ed altro) dell'entità
    // in base all'input del giocatore, esso si muove o spara; l'output è la flag che indica se si è cambiata stanza o meno
    // per appunto segnalarlo al game
    int Player::update(int move) {
        updateNearby();
        int changedRoom = 0;
        switch (move){
            case 'w':
                changedRoom = moveUp();
                break;
            case 's':
                changedRoom = moveDown();
                break;
            case 'a':
                changedRoom = moveLeft();
                break;
            case 'd':
                changedRoom = moveRight();
                break;
            
            case KEY_UP:
                shoot(1);
                break;
            case KEY_DOWN:
                shoot(3);
                break;
            case KEY_LEFT:
                shoot(2);
                break;
            case KEY_RIGHT:
                shoot(4);
                break;
            default:
                break;
        }
        display();
        dungeon->refresh_dungeon();
        return changedRoom;
    }