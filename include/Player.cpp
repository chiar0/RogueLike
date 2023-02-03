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

    bool Player::moveUp(){
        bool result = false;
        wmove(window, positionY, positionX);
        if (nearby[0][1] == ' ') {
            waddch(window, ' ');
            if (positionY < 1) { positionY = 1; }
            else { positionY = positionY - 1; result = true; } 
        }
        display();
        return result;
    }

    bool Player::moveDown(){
        bool result = false;
        wmove(window, positionY, positionX);
        if (nearby[2][1] == ' ') {
            waddch(window, ' ');
            if (positionY > yMax - 2) { positionY = yMax - 2; }
            else { positionY = positionY + 1; result = true; }
        }
        display();
        return result;
    }

    bool Player::moveLeft(){
        bool result = false;
        wmove(window, positionY, positionX);
        if (nearby[1][0] == ' ') {
            waddch(window, ' ');
            if (positionX < 1) { positionX = 1; }
            else { positionX = positionX - 1; result = true; }
        }
        display();
        return result;
    }

    bool Player::moveRight(){
        bool result = false;
        wmove(window, positionY, positionX);
        if (nearby[1][2] == ' ') {
            waddch(window, ' ');
            if (positionX > xMax - 2) { positionX = xMax - 2; }
            else { positionX = positionX + 1; result = true; }
        }
        display();
        return result;
    }

    void Player::attack(int enemyY, int enemyX){
        if (bulletsRemaining > 0) {
            return;
        } else {
            
        }
    }

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

    // metodo invocato per il controllo del cambio stanza
    void Player::checkRoom(char move) {
        bool found = false;
        switch(move) {
            case 'w':
                display::point_list* entry = dungeon->retrive_entry();
                display::point_list* exit = dungeon->retrive_exit();
                while((entry != NULL || exit != NULL) && !found) {
                    if (entry != NULL && entry->p.x == positionX && positionY == 1) {
                        found = true;
                        wmove(window, positionY, positionX);
                        waddch(window, ' ');
                        dungeon->prev_level();
                        window = dungeon->retrive_dungeon();
                        positionY = yMax - 2;
                        display();
                    } else if (exit->p.x == positionX && positionY == 1) {
                        found = true;
                        wmove(window, positionY, positionX);
                        waddch(window, ' ');
                        dungeon->next_level();
                        window = dungeon->retrive_dungeon();
                        positionY = yMax - 2;
                        display();
                    }
                    entry = entry->next;
                    exit = exit->next;
                }
                ;break;
            case 's':
                display::point_list* entry = dungeon->retrive_entry();
                display::point_list* exit = dungeon->retrive_exit();
                while((entry != NULL || exit != NULL) && !found) {
                    if (entry != NULL && entry->p.x == positionX && positionY == yMax - 2) {
                        found = true;
                        wmove(window, positionY, positionX);
                        waddch(window, ' ');
                        dungeon->prev_level();
                        window = dungeon->retrive_dungeon();
                        positionY = 1;
                        display();
                    } else if (exit->p.x == positionX && positionY == yMax - 2) {
                        found = true;
                        wmove(window, positionY, positionX);
                        waddch(window, ' ');
                        dungeon->next_level();
                        window = dungeon->retrive_dungeon();
                        positionY = 1;
                        display();
                    }
                    entry = entry->next;
                    exit = exit->next;
                }
                ;break;
            case 'a':
                display::point_list* entry = dungeon->retrive_entry();
                display::point_list* exit = dungeon->retrive_exit();
                while((entry != NULL || exit != NULL) && !found) {
                    if (entry != NULL && entry->p.y == positionY && positionX == 1) {
                        found = true;
                        wmove(window, positionY, positionX);
                        waddch(window, ' ');
                        dungeon->prev_level();
                        window = dungeon->retrive_dungeon();
                        positionX = xMax - 2;
                        display();
                    } else if (exit->p.y == positionY && positionX == 1) {
                        found = true;
                        wmove(window, positionY, positionX);
                        waddch(window, ' ');
                        dungeon->next_level();
                        window = dungeon->retrive_dungeon();
                        positionX = xMax - 2;
                        display();
                    }
                    entry = entry->next;
                    exit = exit->next;
                }
                ;break;
            case 'd':
                display::point_list* entry = dungeon->retrive_entry();
                display::point_list* exit = dungeon->retrive_exit();
                while((entry != NULL || exit != NULL) && !found) {
                    if (entry != NULL && entry->p.y == positionY && positionX == xMax - 2) {
                        found = true;
                        wmove(window, positionY, positionX);
                        waddch(window, ' ');
                        dungeon->prev_level();
                        window = dungeon->retrive_dungeon();
                        positionX = 1;
                        display();
                    } else if (exit->p.y == positionY && positionX == xMax - 2) {
                        found = true;
                        wmove(window, positionY, positionX);
                        waddch(window, ' ');
                        dungeon->next_level();
                        window = dungeon->retrive_dungeon();
                        positionX = 1;
                        display();
                    }
                    entry = entry->next;
                    exit = exit->next;
                }
                ;break;
        }
    }
 
    // update si occupa di modificare lo stato (come posizione, matrice delle adiacenze ed altro) dell'entità
    int Player::update() {
        updateNearby();
        int move = getch();
        switch (move){
            case 'w':
                if(!moveUp()) { checkRoom(move); }
                ;break;
            case 's':
                if (!moveDown()) { checkRoom(move); }
                ;break;
            case 'a':
                if (!moveLeft()) { checkRoom(move); }
                ;break;
            case 'd':
                if(!moveRight()) { checkRoom(move); }
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