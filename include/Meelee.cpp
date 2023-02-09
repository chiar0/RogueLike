#include "Meelee.hpp"

    // costruttore
    Meelee::Meelee(int positionX, int positionY, int HP, int damage, bool isBoss, engine* dungeon, BulletList* bulletsList)
    :Entity(positionX, positionY, HP, damage, dungeon, bulletsList) {

        this->isBoss = isBoss;
        this->isTaunted = false; // ogni nemico corpo a corpo di base non è "taunted"
        this->chaseBlocks = 7; // ogni nemico corpo a corpo di base segue il player per 7 mosse se taunted
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
                        moveRight();
                        attack(4, playerX, playerY);
                        break;
                    case 2:
                        moveLeft();
                        attack(2, playerX, playerY);
                        break;
                    case 3:
                        moveUp();
                        attack(1, playerX, playerY);
                        break;
                    case 4:
                        moveDown();
                        attack(3, playerX, playerY);
                        break;
                    default:
                        break;
                }
            }
        }
        display();
    }

    int Meelee::attack(int direction, int playerX, int playerY){
        char mapChar;
        int dimension = 3, bossBoost = 0;
        int directionX = 0, directionY = 0;
        int attackX = 0, attackY = 0;
        int damageDealt = 0;
        int enemyX = Entity::getPositionX(), enemyY = Entity::getPositionY();

        if(isBoss){
            bossBoost = bossBoost + 2;
        }
        switch(direction){
            case 1:
                directionY -= (dimension + bossBoost); 
                directionX -= (dimension + bossBoost);
                directionX /= 2;              
                ;break;
            case 2:
                directionX -= (dimension + bossBoost);
                directionY -= (dimension + bossBoost);
                directionY /= 2;
                ;break;
            case 3:
                directionY += 1;
                directionX -= (dimension + bossBoost);
                directionX /= 2;
                ;break;
            case 4:
                directionX += 1;
                directionY -= (dimension + bossBoost);
                directionY /= 2;
                ;break;
            default:
                ;break;
        }
        display::point p;
        for(int i = 0; i < (dimension + bossBoost); i++){
            for(int j = 0; j < (dimension + bossBoost); j++){
                attackX = enemyX + directionX + i;
                attackY = enemyY + directionY + j;
                mapChar = mvwinch(dungeon->retrive_dungeon(), attackY, attackX);
                p = {attackY, attackX};
                if(mapChar == '@'){
                    damageDealt += this->damage;
                if(mapChar == ' ')
                    dungeon->write_char(p, '#');
                }
            }
        }
        if(mvwinch(dungeon->retrive_dungeon(),attackY, attackY) == '#'){
                    endwin();
                    printf("test");
                    exit(1);  
                }
        return damageDealt;
    }



