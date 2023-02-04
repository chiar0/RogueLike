#include "Ranged.hpp"

    Ranged::Ranged(int positionX, int positionY, int HP, int damage, int range, bool isBoss, engine* dungeon, char character, int id)
    :Entity(positionX, positionY, HP, damage, dungeon, character) {
        this->id = id;
        this->range = range;
        this->isBoss = isBoss;
    }

    // getters
    int Ranged::getId() { return id; }
    int Ranged::getRange() { return range; }
    bool Ranged::getIsBoss() { return isBoss; }

    void Ranged::update(int playerX, int playerY) {

        updateNearby(); // aggiorno le entità vicine
        int dx = abs(playerX - positionX);
        int dy = abs(playerY - positionY);
        int distance = sqrt(dx * dx + dy * dy);
        if (dx <= range || dy <= range) {
            if (positionX == playerX) {
                // shoot up or down
            } else if (positionY == playerY) {
                // shoot left or right
            }
        } else {
            int movementChance, direction;
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
