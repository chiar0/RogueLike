#pragma once

#include "Entity.hpp"
#include <time.h>
#include <math.h>
#include <cstdlib>

class Ranged: public Entity {

protected:

    int range; // distanza massima di attacco
    bool isBoss; // = true se è un boss (più forte, più vita, più danno)

public:

    Ranged(int positionX, int positionY, int room, int HP, int damage, int range, bool isBoss, engine* dungeon, char character);

    // getters
    int getRange();
    bool getIsBoss();

    // setters
    void setRange(int range);

    // update con movimento non certo in direzioni casuali (se non in range), movimento in direzione del player se in range,
    // attacco se in range e se su stessa riga o colonna
    void update(int playerX, int playerY);

};