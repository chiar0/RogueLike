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

    // setters
    void Player::setRange(int increase) { range += increase; }
    void Player::setScore(int increase) { score += increase; }
    void Player::setCollectedArtifacts() { collectedArtifacts += 1; }

    // metodi per il movimento:
    // cotrolla se la casella in cui si vuole andare è vuota (con la matrice di adiacenze), se lo è allora si sposta
    // se si è arrivati alla fine della stanza si hiama la funzione di cambio stanza con la direzione corrispondente
    // se non si è arrivati alla fine della stanza si chiama la funzione di display per aggiornare la posizione del giocatore

    bool Player::moveUp() {
        bool flag = false;
        if (nearby[0][1] == ' ' || nearby[0][1] == '+') {
            hide();
            positionY = positionY - 1;
        } else if (nearby[0][1] == 'a') {
            hide();
            positionY = positionY - 1;
            setCollectedArtifacts();
        }
        if (positionY == 0) { flag = true; changeRoom(0); }
        return flag;
    }

    bool Player::moveDown() {
        bool flag = false;
        if (nearby[2][1] == ' ' || nearby[2][1] == '+') {
            hide();
            positionY = positionY + 1;
        } else if (nearby[2][1] == 'a') {
            hide();
            positionY = positionY - 1;
            setCollectedArtifacts();
        }
        if (positionY == yMax-1) { flag = true; changeRoom(1); }
        return flag;
    }

    bool Player::moveLeft() {
        bool flag = false;
        if (nearby[1][0] == ' ' || nearby[1][0] == '+') {
            hide();
            positionX = positionX - 1;
        } else if (nearby[1][0] == 'a') {
            hide();
            positionY = positionY - 1;
            setCollectedArtifacts();
        }
        if (positionX == 0) { flag = true; changeRoom(2); }
        return flag;
    }

    bool Player::moveRight() {
        bool flag = false;
        if (nearby[1][2] == ' ' || nearby[1][2] == '+') {
            hide();   
            positionX = positionX + 1;
        } else if (nearby[1][2] == 'a') {
            hide();
            positionY = positionY - 1;
            setCollectedArtifacts();
        }
        if (positionX == xMax-1) { flag = true; changeRoom(3); }
        return flag;
    }

    void Player::shoot(int direction){
        Entity::addBullets(direction, true);
    }


    // metodo per impostare il puntatore alla lista di nemici corrente
    // non effettuo il controllo se la lista esiste perchè nella head c'è sempre una lista di nemici

    // metodo per cambiare stanza
    // se la direction corrisponde al campo NSWE di un'uscita/entrata, allora (dato che si è arrivati alla fine della stanza)
    // si chiama la funzione next_level() se la porta è di uscita, prev_level() se la porta è di entrata
    // si aggiorna la posizione del giocatore con quella dell'entrata/uscita confrontando la posizione del giocatore con quella delle porte
    // della stanza successiva in maniera duale (se si è entrati in un uscita allora si confronta con l'entrata della stanza successiva e viceversa)
  
    bool Player::changeRoom(int direction) {

        int entry_NSWE = dungeon->retrive_entry_NSWE();
        int exit_NSWE = dungeon->retrive_exit_NSWE();
        bool flag;

        if (direction == exit_NSWE) {
            /*
            wmove(dungeon->retrive_dungeon(), positionY, positionX);
            waddch(dungeon->retrive_dungeon(), ' ');
            current->list.hideAll();
            dungeon->next_level();
            if (dungeon->retrive_level_number() > maxId) { newList(4, 4, this->dungeon); }
            nextList();

            display::point_list *tmp = dungeon->retrive_entry();
            while(tmp->p.x != getPositionX() && tmp->p.y != getPositionY()) {
                tmp = tmp->next;
            }
            positionX = tmp->p.x;
            positionY = tmp->p.y;
            */
           flag = true;

        } else if (direction == entry_NSWE) {
            /*
            wmove(dungeon->retrive_dungeon(), positionY, positionX);
            waddch(dungeon->retrive_dungeon(), ' ');
            current->list.hideAll();
            dungeon->prev_level();
            prevList();

            display::point_list *tmp = dungeon->retrive_exit();
            while(tmp->p.x != getPositionX() && tmp->p.y != getPositionY()) {
                tmp = tmp->next;
            }
            positionX = tmp->p.x;
            positionY = tmp->p.y;
            */
           flag = false;
        }

        return flag;

    }

    // metodo invocato quando viene sconfitto un nemico
    void Player::defeatedEnemy(bool isBoss) {
        if (isBoss) { setScore(1500); }
        else { setScore(500); }
    }
 
    // update si occupa di modificare lo stato (come posizione, matrice delle adiacenze ed altro) dell'entità
    char Player::update(int move) { 
        switch (move){
            case 'w':
                moveUp();
                ;break;
            case 's':
                moveDown();
                ;break;
            case 'a':
                moveLeft();
                ;break;
            case 'd':
                moveRight();
                ;break;
            
            case KEY_UP:
                shoot(1);
                ;break;
            case KEY_DOWN:
                shoot(3);
                ;break;
            case KEY_LEFT:
                shoot(2);
                ;break;
            case KEY_RIGHT:
                shoot(4);
                ;break;
            
            default:
                ;break;
        }
        display();
        dungeon->refresh_dungeon();
        return move;
    }