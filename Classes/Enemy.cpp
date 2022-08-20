#include "Enemy.hpp"

    Enemy::Enemy(int positionX, int positionY, int room, int HP, int damage, bool isBoss, int chaseBlocks): Entity(
            positionX, positionY, room, HP, WINDOW* window, char character) {
        this->damage = damage;
        this->isBoss = isBoss;
        this->chaseBlocks = chaseBlocks;
        this->currentChaseBlocks = chaseBlocks;
    }

    int Enemy::getDamage() { return this->damage; }
    bool Enemy::getIsBoss() { return this->isBoss; }

    void Enemy::update(int playerX, int playerY, bool isTaunted) {
        this->isTaunted = isTaunted;
        if (isTaunted) {
            if (playerX == getPositionX()) {
                if (playerY > getPositionY()) { moveDown(); }
                else { moveUp(); }
            } else if (playerY == getPositionY()) {
                if (playerX > getPositionX()) { moveRight(); }
                else { moveLeft(); }
            }
            currentChaseBlocks -= 1;
            if (currentChaseBlocks == 0) {
                this->isTaunted = false;
                currentChaseBlocks = chaseBlocks;
            }
        } else {
            int movementChance;
            movementChance = rand()% 3+1;
            if (movementChance == 3) {
                int direction;
                direction = rand()% 4+1;
                switch (direction) {
                    case 1:
                        moveRight()
                        ;break;
                    case 2:
                        moveLeft()
                        ;break;
                    case 3:
                        moveUp()
                        ;break;
                    case 4:
                        moveDown()
                        ;break;
                }
            }
        }
    }