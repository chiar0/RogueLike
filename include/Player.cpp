#include "Player.hpp"

    Player::Player(int positionX, int positionY, int HP, int damage, engine* dungeon)
    :Entity(positionX, positionY, HP, damage, dungeon) {
        this->score = 0;
        this->range = 4;
        this->collectedArtifacts = 0;
        this->bulletsRemaining = 0;
        this->character = '@';
        this->head = new listOfLists(List(5, 5, dungeon, 0));
        this->current = &(head->list);
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

    void Player::moveUp() {
        if (nearby[0][1] == ' ' || nearby[0][1] == '+') {
            hide();
            positionY = positionY - 1;
        } else if (nearby[0][1] == 'a') {
            hide();
            positionY = positionY - 1;
            setCollectedArtifacts();
        }
        if (positionY == 0) { changeRoom(0); }
    }

    void Player::moveDown() {
        if (nearby[2][1] == ' ' || nearby[2][1] == '+') {
            hide();
            positionY = positionY + 1;
        } else if (nearby[2][1] == 'a') {
            hide();
            positionY = positionY - 1;
            setCollectedArtifacts();
        }
        if (positionY == yMax-1) { changeRoom(1); }
    }

    void Player::moveLeft() {
        if (nearby[1][0] == ' ' || nearby[1][0] == '+') {
            hide();
            positionX = positionX - 1;
        } else if (nearby[1][0] == 'a') {
            hide();
            positionY = positionY - 1;
            setCollectedArtifacts();
        }
        if (positionX == 0) { changeRoom(2); }
    }

    void Player::moveRight() {
        if (nearby[1][2] == ' ' || nearby[1][2] == '+') {
            hide();   
            positionX = positionX + 1;
        } else if (nearby[1][2] == 'a') {
            hide();
            positionY = positionY - 1;
            setCollectedArtifacts();
        }
        if (positionX == xMax-1) { changeRoom(3); }
    }

    // metodo per cambiare stanza
    // se la direction corrisponde al campo NSWE di un'uscita/entrata, allora (dato che si è arrivati alla fine della stanza)
    // si chiama la funzione next_level() se la porta è di uscita, prev_level() se la porta è di entrata
    // si aggiorna la posizione del giocatore con quella dell'entrata/uscita confrontando la posizione del giocatore con quella delle porte
    // della stanza successiva in maniera duale (se si è entrati in un uscita allora si confronta con l'entrata della stanza successiva e viceversa)
    void Player::changeRoom(int direction) {

        int entry_NSWE = dungeon->retrive_entry_NSWE();
        int exit_NSWE = dungeon->retrive_exit_NSWE();;

        if (direction == exit_NSWE) {
            wmove(dungeon->retrive_dungeon(), positionY, positionX);
            waddch(dungeon->retrive_dungeon(), ' ');
            current->hideAll();
            dungeon->next_level();
            if (dungeon->retrive_level_number() > maxId) { newList(5, 5, this->dungeon); }
            setCurrent(dungeon->retrive_level_number());

            display::point_list *tmp = dungeon->retrive_entry();
            while(tmp->p.x != getPositionX() && tmp->p.y != getPositionY()) {
                tmp = tmp->next;
            }
            positionX = tmp->p.x;
            positionY = tmp->p.y;
        } else if (direction == entry_NSWE) {

            wmove(dungeon->retrive_dungeon(), positionY, positionX);
            waddch(dungeon->retrive_dungeon(), ' ');
            current->hideAll();
            dungeon->prev_level();
            setCurrent(dungeon->retrive_level_number());

            display::point_list *tmp = dungeon->retrive_exit();
            while(tmp->p.x != getPositionX() && tmp->p.y != getPositionY()) {
                tmp = tmp->next;
            }
            positionX = tmp->p.x;
            positionY = tmp->p.y;
        }
    }

    void Player::setCurrent(int id) {
        listOfLists *tmp = head;
        while (head->list.getId() != id) {
            head = head->next;
        }
        current = &(head->list);
        head = tmp;
    }

    void Player::newList(int nMeelee, int nRanged, engine* dungeon) {
        listOfLists *tmp = head;
        maxId += 1;
        List new_list(nMeelee, nRanged, dungeon, maxId);
        while(head->next != NULL) {
            head = head->next;
        }
        head->next = new listOfLists(new_list);
        head = head->next;
        head->next = NULL;
        head = tmp;
    }

    // metodo invocato quando viene sconfitto un nemico
    void Player::defeatedEnemy(bool isBoss) {
        if (isBoss) { setScore(1500); }
        else { setScore(500); }
    }
 
    // update si occupa di modificare lo stato (come posizione, matrice delle adiacenze ed altro) dell'entità
    char Player::update() { 
        updateNearby();
        int move = getch();
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
            
            /*
            case KEY_UP:
                attackUp();
            case KEY_DOWN:
                attackDown();
            case KEY_LEFT:
                attackLeft();
                ;break;
            case KEY_RIGHT:
                attackRight();
                ;break;
            */
            default:
                ;break;
        }
        display();
        current->updateAll(positionX, positionY);
        dungeon->refresh_dungeon();
        return move;
    }

