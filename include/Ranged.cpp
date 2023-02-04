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

    // setters
    void Ranged::setRange(int range) { range = range; }

    void Ranged::update(int playerX, int playerY) {
        int dx = playerX - positionX;
        int dy = playerY - positionY;
        int distance = sqrt(dx * dx + dy * dy);
        if (distance <= range) {
            if (positionX == playerX) {
                // shoot up or down
            } else if (positionY == playerY) {
                // shoot left or right
            } else {
                bool direction = abs(dx) < abs(dy);
                if (direction) {
                    if (dx > 0) { moveRight(); }
                    else { moveLeft(); }
                } else {
                    if (dy > 0) { moveDown(); }
                    else { moveUp(); }
                }
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
    }
