#include "Meelee.hpp"

    // costruttore
    Meelee::Meelee(int positionX, int positionY, int HP, int damage, bool isBoss, int chaseBlocks, engine* dungeon, BulletList* bulletsList)
    :Entity(positionX, positionY, HP, damage, dungeon, bulletsList) {

        this->isBoss = isBoss;
        this->isTaunted = false; // ogni nemico corpo a corpo di base non è "taunted"
        this->chaseBlocks = chaseBlocks;
        this->currentChaseBlocks = chaseBlocks;
        this->character = 'M';
        updateNearby(); // aggiorno le entità vicine
    }

    // getters
    bool Meelee::getIsBoss() { return this->isBoss; }
    bool Meelee::getIsTaunted() { return this->isTaunted; }
    int Meelee::getCurrentChaseBlocks() { return this->currentChaseBlocks; }

    // setters
    void Meelee::setIsTaunted(bool isTaunted) { this->isTaunted = isTaunted; }

    // update con movimento non certo in direzioni casuali (dx, sx, up, down), altrimenti segue il player se è "taunted"
    void Meelee::update(int playerX, int playerY) {

        int direction;
        updateNearby(); // aggiorno le entità vicine

        // se il nemico è "taunted" allora si muove verso il player
        if (isTaunted) {
            int diffX, diffY;
            diffX = getPositionX() - playerX;
            diffY = getPositionY() - playerY;
            if (abs(diffX) > abs(diffY)) {
                if (diffX > 0) {
                    moveLeft();
                } else {
                    moveRight();
                }
            } else {
                if (diffY > 0) {
                    moveUp();
                } else {
                    moveDown();
                }
            }
            
            // decremento ad ogni update i chaseblocks rimanenti, per poi resettarli e togliere il taunt quanto raggiungono 0
            currentChaseBlocks -= 1;
            if (currentChaseBlocks == 0) {
                this->isTaunted = false;
                currentChaseBlocks = chaseBlocks;
            }
            
        // se il nemico non è "taunted" allora si muove in direzioni casuali
        } else {
            int movementChance;
            movementChance = rand()% 3;
            if (movementChance != 0) {
                direction = rand()% 4+1;
                switch (direction) {
                    case 1:
                        moveRight(); break;
                    case 2:
                        moveLeft(); break;
                    case 3:
                        moveUp(); break;
                    case 4:
                        moveDown(); break;
                    default:
                        break;
                }
            }
        }
        display();
    }

    int Meelee::attack(int direction, int playerX, int playerY){
        char mapChar;
        int dimension = 3;
        int directionX = 0, directionY = 0;
        int isBossBoost = 0;
        if(isBoss){
            isBossBoost = isBossBoost + 2;
        }
        switch(direction){
            case 1:
                directionX -= (dimension + isBossBoost); 
                directionY -= (dimension + isBossBoost);
                directionY               
                ;break;
            case 2:

        }
        for(int i = 0; i < dimension; i++){
            for(int j = 0; j < dimension; i++){
                mapChar = mvwinch(dungeon->retrive_dungeon(), positionY, positionX)
            }
        }

    }



