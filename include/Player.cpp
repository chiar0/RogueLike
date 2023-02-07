#include "Player.hpp"

    Player::Player() : Entity(){};

    Player::Player(int positionX, int positionY, int HP, int damage, engine* dungeon, char character, BulletList* bulletsList)
    :Entity(positionX, positionY, HP, damage, dungeon, character, bulletsList) {
        this->score = 0;
        this->collectedArtifacts = 0;
        this->bulletsRemaining = 0;
        updateNearby();
    }

    // getters
    int Player::getRange() { return range; }
    int Player::getScore() { return score; }
    int Player::getCollectedArtifacts() {return collectedArtifacts; }

    // setters
    void Player::setRange(int range) { range = range; }
    void Player::setScore(int increase) { score += increase; }
    void Player::setCollectedArtifacts() { collectedArtifacts += 1; }

    // metodi per il movimento:
    // cotrolla se la casella in cui si vuole andare è vuota (con la matrice di adiacenze), se lo è allora si sposta
    // se si è arrivati alla fine della stanza si hiama la funzione di cambio stanza con la direzione corrispondente
    // se non si è arrivati alla fine della stanza si chiama la funzione di display per aggiornare la posizione del giocatore

    void Player::moveUp(){
        wmove(dungeon->retrive_dungeon(), positionY, positionX);
        if (nearby[0][1] == ' ') {
            waddch(dungeon->retrive_dungeon(), ' ');
            positionY = positionY - 1;
        }
        if (positionY == 0) { changeRoom(0); }
    }

    void Player::moveDown(){
        wmove(dungeon->retrive_dungeon(), positionY, positionX);
        if (nearby[2][1] == ' ') {
            waddch(dungeon->retrive_dungeon(), ' ');
            positionY = positionY + 1;
        }
        if (positionY == yMax-1) { changeRoom(1); }
    }

    void Player::moveLeft(){
        wmove(dungeon->retrive_dungeon(), positionY, positionX);
        if (nearby[1][0] == ' ') {
            waddch(dungeon->retrive_dungeon(), ' ');
            positionX = positionX - 1;
        }
        if (positionX == 0) { changeRoom(2); }
    }

    void Player::moveRight(){
        wmove(dungeon->retrive_dungeon(), positionY, positionX);
        if (nearby[1][2] == ' ') {
            waddch(dungeon->retrive_dungeon(), ' ');    
            positionX = positionX + 1;
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
            dungeon->next_level();
            display::point_list *tmp = dungeon->retrive_entry();
            while(tmp->p.x != getPositionX() && tmp->p.y != getPositionY()) {
                tmp = tmp->next;
            }
            positionX = tmp->p.x;
            positionY = tmp->p.y;
        } else if (direction == entry_NSWE) {
            wmove(dungeon->retrive_dungeon(), positionY, positionX);
            waddch(dungeon->retrive_dungeon(), ' ');
            dungeon->prev_level();
            display::point_list *tmp = dungeon->retrive_exit();
            while(tmp->p.x != getPositionX() && tmp->p.y != getPositionY()) {
                tmp = tmp->next;
            }
            positionX = tmp->p.x;
            positionY = tmp->p.y;
        }
    }

    void Player::attack(int enemyY, int enemyX){ }

    void Player::attackUp() {
        if (getPositionY() != 2) {
            if (getNearby(0, 1) == 'E') {
                attack(getPositionY() - 1, getPositionX());
            }
        }
    }

    void Player::attackDown() {
        if (getPositionY() != getMaxY() - 3) {
            if (getNearby(2, 1) == 'E') {
                attack(getPositionY() + 1, getPositionX());
            }
        }
    }

    void Player::attackLeft() {
        if (getPositionX() != 2) {
            if (getNearby(1, 0) == 'E') {
                attack(getPositionY(), getPositionX() - 1);
            }
        }
    }

    void Player::attackRight() {
        if (getPositionX() != getMaxX() - 3) {
            if (getNearby(1, 2) == 'E') {
                attack(getPositionY(), getPositionX() + 1);
            }
        }
    }

    // metodo invocato quando viene sconfitto un nemico
    void Player::defeatedEnemy(bool isBoss) {
        if (isBoss) { setScore(1500); }
        else { setScore(500); }
    }
 
    // update si occupa di modificare lo stato (come posizione, matrice delle adiacenze ed altro) dell'entità
    int Player::update(int move) {
        updateNearby();
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
        return move;
    }

    /*
    int Player::updateBullet(){
        Bul aux = first, prev = first;
        bool alive = false;
        int hit = 0;

        prev = first;

        if(first != NULL){
            while(aux != NULL){
                //rimuovo il proiettile dalla posizione attuale
                display::point p{aux->bullet.gety(), aux->bullet.getx()};
                dungeon->write_char(p, ' ');
                //mvwprintw(dungeon->retrive_dungeon(), aux->bullet.gety(), aux->bullet.getx(), "%c", ' ');
                //lo muovo e verifico se è finito su qualche entità/muro
                alive = aux->bullet.move();

                //lo tengo se colpisco il personaggio oppure niente
                if(alive == true || (aux->bullet.getx() == Player::getPositionX() && aux->bullet.gety() == Player::getPositionY())){
                    display::point p{aux->bullet.gety(), aux->bullet.getx()};
                    dungeon->write_char(p, aux->bullet.getChar());
                    //mvwprintw(dungeon->retrive_dungeon(), aux->bullet.gety(), aux->bullet.getx(), "%c", aux->bullet.getChar());
                    //aux->bullet.display();
                    prev = aux;
                    aux = aux->next;
                }

                else{
                    //verifico se colpisco un nemico e in caso affermativo lo aggiorno
                    char mapChar = mvwinch(dungeon->retrive_dungeon(), aux->bullet.gety(), aux->bullet.getx());
                    if(mapChar == 'R' || mapChar == 'M'){
                        enemys->isHit(aux->bullet.getx(), aux->bullet.gety(), damage);
                        hit = 1;
                    }

                    //altrimenti lo elimino dalla lista
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

        return hit;
    }; 
    */

    void Player::shoot(int direction){
        Entity::addBullets(direction, true);
    }
