#include "Player.hpp"

    Player::Player(int positionX, int positionY, int room, int HP, int damage): Entity(positionX, positionY, room, HP, WINDOW* window,
                                                                               char character) {
        this->damage = damage;
        this->score = 0;
        this->collectedArtifacts = 0;
    }

    int Player::getDamage() { return damage; }
    int Player::getScore() { return score; }
    int Player::getCollectedArtifacts() {return collectedArtifacts; }

    void Player::artifactCollected() {
        setCollectedArtifacts();
        setDamage();
    }

    void Player::defeatedEnemy(bool isBoss) {
        if (isBoss) { setScore(1500); }
        else { setScore(500); }
    }

    void Player::update() {
        int move = wgetch(getWindow());
        switch (move){
            case (int)'w':
                moveUp();
            ;break;
            case (int)'s':
                moveDown();
                ;break;
            case (int)'a':
                moveLeft();
                ;break;
            case (int)'d':
                moveRight();
                ;break;
            default: break;
        }
    }