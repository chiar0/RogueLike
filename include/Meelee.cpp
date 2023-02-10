#include "Meelee.hpp"

    // costruttore
    Meelee::Meelee(int positionX, int positionY, int HP, int damage, bool isBoss, engine* dungeon, BulletList* bulletsList)
    :Entity(positionX, positionY, HP, damage, dungeon, bulletsList) {

        this->isBoss = isBoss;
        this->isTaunted = false;    // ogni nemico corpo a corpo di base non è "taunted"
        this->chaseBlocks = 7;      // ogni nemico corpo a corpo di base segue il player per 7 mosse se taunted
        this->currentChaseBlocks = chaseBlocks;
        this->character = 'M';
        updateNearby();             // aggiorno la matrice delle entità vicine
        this->startAttackX = 0;
        this->startAttackY = 0;
    }

    // getters
    bool Meelee::getIsBoss() { return this->isBoss; }
    bool Meelee::getIsTaunted() { return this->isTaunted; }
    int Meelee::getCurrentChaseBlocks() { return this->currentChaseBlocks; }

    // setters
    void Meelee::setIsTaunted(bool isTaunted) { this->isTaunted = isTaunted; }

    // controlla se il nemico è in range di attacco in una certa direzione usando la matrice di adiacenza
    bool Meelee::isInRange(int x, int y, int direction) {
        bool found = false;
        switch (direction) {
            case 1:
                // sopra
                if (positionX == x && (positionY-1 == y || positionY-2 == y)) { found = true; }
                else { found = false; }
                break;
            case 2:
                // sotto
                if (positionX == x && (positionY+1 == y || positionY+2 == y)){found = true; }
                else{ found = false; }
                break;
            case 3:
                // destra
                if (positionY == y && (positionX+1 == x || positionX+1 == x)){ found = true; }
                else{ found = false; }
                break;
            case 4:
                // sinistra
                if (positionY == y && (positionX-1 == x-1 || positionX-1 == x)){ found = true; }
                else{ found = false; }
                break;
        }
        return found;
    }

    // update con movimento non certo in direzioni casuali (dx, sx, up, down), altrimenti segue il player se è "taunted"
    int Meelee::update(int playerX, int playerY) {
        int damageDealt = 0;
        int direction;
        updateNearby(); // aggiorno le entità vicine

        // controllo se il nemico è vicino al player, in caso affermativo lo "taunto"
        bool isPlayerNearby = false;
        for (int i = 0; i < 4 && !isPlayerNearby; i++) { isPlayerNearby = isInRange(playerX, playerY, i+1); }
        if (isPlayerNearby) { isTaunted = true; }

        // se il nemico è "taunted" allora si muove verso il player
        if (isTaunted) {
            // controllo la distanza tra il nemico e il player, se il player è in range allora attacco
            // altrimenti mi muovo verso il player
            int diffX, diffY;
            diffX = getPositionX() - playerX;
            diffY = getPositionY() - playerY;
            if (abs(diffX) > abs(diffY)) {
                if (diffX > 0) {
                    moveLeft();
                    if(startAttackX == 0 && startAttackY == 0){
                        if(isInRange(playerX, playerY, 4))  
                            damageDealt = attack(2, playerX, playerY); 
                    }
                    else
                        clearAttack();
                } else {
                    moveRight();
                    if(startAttackX == 0 && startAttackY == 0){
                        if(isInRange(playerX, playerY, 3))  
                            damageDealt = attack(4, playerX, playerY); 
                    }
                    else
                        clearAttack();
                }
            } else {
                if (diffY > 0) {
                    moveUp();
                    if(startAttackX == 0 && startAttackY == 0){
                        if(isInRange(playerX, playerY, 1))  
                            damageDealt = attack(1, playerX, playerY); 
                    }
                    else
                        clearAttack();
                } else {
                    moveDown();
                    if(startAttackX == 0 && startAttackY == 0){
                        if(isInRange(playerX, playerY, 2))  
                            damageDealt = attack(3, playerX, playerY); 
                    }
                    else
                        clearAttack();
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
                        clearAttack();
                        break;
                    case 2:
                        moveLeft();
                        clearAttack();
                        break;
                    case 3:
                        moveUp();
                        clearAttack();
                        break;
                    case 4:
                        moveDown();
                        clearAttack();
                        break;
                    default:
                        break;
                }
            }
        }
        display();
        return damageDealt;
    }

    int Meelee::attack(int direction, int playerX, int playerY){
        
        char mapChar;
        int dimension = 3, bossBoost = 0;
        int attackX = 0, attackY = 0;
        int damageDealt = 0;
        int enemyX = Entity::getPositionX(), enemyY = Entity::getPositionY();

        if(isBoss){
            bossBoost = bossBoost + 2;
        }
        switch(direction){
            case 1:
                startAttackY -= (dimension + bossBoost); 
                startAttackX -= (dimension + bossBoost);
                startAttackX /= 2;              
                ;break;
            case 2:
                startAttackX -= (dimension + bossBoost);
                startAttackY -= (dimension + bossBoost);
                startAttackY /= 2;
                ;break;
            case 3:
                startAttackY += 1;
                startAttackX -= (dimension + bossBoost);
                startAttackX /= 2;
                ;break;
            case 4:
                startAttackX += 1;
                startAttackY -= (dimension + bossBoost);
                startAttackY /= 2;
                ;break;
            default:
                ;break;
        }
        for(int i = 0; i < (dimension + bossBoost); i++){
            for(int j = 0; j < (dimension + bossBoost); j++){
                attackX = enemyX + startAttackX + i;
                attackY = enemyY + startAttackY + j;
                mapChar = mvwinch(Entity::getDungeonWindow(), attackY, attackX);
                if(mapChar == '@')
                    damageDealt += this->damage;
                if(mapChar == ' '){
                    wmove(Entity::getDungeonWindow(), attackY, attackX);
                    waddch(Entity::getDungeonWindow(), '#');
                }
            }
        }
        this->startAttackX += enemyX;
        this->startAttackY += enemyY;
        return damageDealt;
    }

    void Meelee::clearAttack() {
        int bossBoost = 0;
        int attackX = 0, attackY = 0;
        int dimension = 3;
        char mapChar;
        if (isBoss) { bossBoost = bossBoost + 2; }
        for(int i = 0; i < (dimension + bossBoost); i++){
            for(int j = 0; j < (dimension + bossBoost); j++){
                attackX = startAttackX + i;
                attackY = startAttackY + j;
                mapChar = mvwinch(Entity::getDungeonWindow(), attackY, attackX);
                if(mapChar == '#'){
                    wmove(Entity::getDungeonWindow(), attackY, attackX);
                    waddch(Entity::getDungeonWindow(), ' ');
                }
            }
        }
        this->startAttackX = 0;
        this->startAttackY = 0;
    }



