#include "Player.hpp"

    Player::Player(int positionX, int positionY, int room, int HP, int damage, engine* dungeon, char character)
    :Entity(positionX, positionY, room, HP, damage, dungeon, character) {
        this->score = 0;
        this->collectedArtifacts = 0;
        this->bulletsRemaining = 0;
        updateNearby();
    }

    // getters
    int Player::getRange() { return range; }
    int Player::getScore() { return score; }
    int Player::getCollectedArtifacts() {return collectedArtifacts; }
    // level Player::getRoom() { return room; }

    // setters
    void Player::setRange(int range) { range = range; }
    void Player::setScore(int increase) { score += increase; }
    void Player::setCollectedArtifacts() { collectedArtifacts += 1; }
    // void Player::setRoom(level room) { this->room = room; }

    void Player::moveUp(){
        wmove(dungeon->retrive_dungeon(), positionY, positionX);
        if (nearby[0][1] == ' ') {
            waddch(dungeon->retrive_dungeon(), ' ');
            // if (positionY < 0) { positionY = 0; }
            positionY = positionY - 1;
        }
        if (positionY == 0) { changeRoom(0); }
        else { display(); }
    }

    void Player::moveDown(){
        wmove(dungeon->retrive_dungeon(), positionY, positionX);
        if (nearby[2][1] == ' ') {
            waddch(dungeon->retrive_dungeon(), ' ');
            // if (positionY > yMax-1) { positionY = yMax-1; }
            positionY = positionY + 1;
        }
        if (positionY == yMax-1) { changeRoom(1); }
        else { display(); }
    }

    void Player::moveLeft(){
        wmove(dungeon->retrive_dungeon(), positionY, positionX);
        if (nearby[1][0] == ' ') {
            waddch(dungeon->retrive_dungeon(), ' ');
            // if (positionX < 0) { positionX = 0; }
            positionX = positionX - 1;
        }
        if (positionX == 0) { changeRoom(2); }
        else { display(); }
    }

    void Player::moveRight(){
        wmove(dungeon->retrive_dungeon(), positionY, positionX);
        if (nearby[1][2] == ' ') {
            waddch(dungeon->retrive_dungeon(), ' ');    
            // if (positionX > xMax-1) { positionX = xMax-1; }
            positionX = positionX + 1;
        }
        if (positionX == xMax-2) { changeRoom(3); }
        else { display(); }
    }

    // metodo per cambiare stanza
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
        dungeon->refresh_dungeon();
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
    int Player::update() {
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
        dungeon->refresh_dungeon();
        return move;
    }