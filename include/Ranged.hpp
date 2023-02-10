#pragma once

#include "Entity.hpp"
#include <time.h>
#include <math.h>
#include <cstdlib>

class Ranged: public Entity {

protected:

    int range;      // distanza massima di attacco
    bool isBoss;       // = true se è un boss (più forte, più vita, più danno)

public:

    // costruttore
    Ranged(int positionX, int positionY, int HP, int damage, int range, bool isBoss, engine* dungeon, BulletList* bulletsList);

    // getters
    int getRange();
    bool getIsBoss();

    // setters
    void setRange(int range);
    
    // update per l'aggiornamento dell'entità, in base a quanto è distante dal player decide se sparare o meno
    void update(int playerX, int playerY);

    // metodo per sparare in una certa direzione
    void shoot(int direction);

};