#pragma once

#include "Entity.hpp"
#include <time.h>
#include <cstdlib>

// Classe usata per i nemici
class Meelee: public Entity {

protected:
    bool isBoss; // = true se è un boss (più forte, più vita, più danno)
    bool isTaunted; // se = true, il nemico si muove verso il player per n = chaseBlocks mosse
    int chaseBlocks; 
    int currentChaseBlocks; // numero di caselle per le quali il nemico deve ancora seguire il player prima di smettere di essere "taunted"

public:
    Meelee(int positionX, int positionY, int room, int HP, int damage, bool isBoss, int chaseBlocks, engine* dungeon, char character);

    // getters
    bool getIsBoss();
    bool getIsTaunted();
    int getCurrentChaseBlocks();

    // setters
    void setIsTaunted(bool isTaunted);

    // update con movimento non certo in direzioni casuali (dx, sx, up, down)
    void update(int playerX, int playerY);
};