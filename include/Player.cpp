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